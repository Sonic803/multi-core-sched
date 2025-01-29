import colorsys
import json
import matplotlib.pyplot as plt
import numpy as np
import math
import random
from statsmodels.stats.diagnostic import acorr_ljungbox

def getColors(numColors, numVariations):
    colors = []
    for i in range(numColors):
        base_hue = i / numColors  # Base hue for this color group
        colors.append([])
        for j in range(numVariations):
            # Introduce hue variation (±2.5% maximum from base hue)
            hue_variation = 0.2  # Adjust this value to control hue variation strength
            hue = (base_hue + ((j/numVariations) - 0.5) * hue_variation) % 1
            
            # Original brightness progression with modified parameters
            lightness = 0.4 + j/numVariations/2.5  # 0.4 to 0.8 lightness range
            saturation = 0.8 - j/numVariations/4  # 0.7 to 0.45 saturation range
            
            colors[i].append(colorsys.hls_to_rgb(
                hue, 
                lightness, 
                saturation
            ))
    return colors

def showColors():
    # Plot colors
    fig, ax = plt.subplots(figsize=(numVariations, numColors))
    for i, row in enumerate(colors):
        for j, color in enumerate(row):
            ax.add_patch(plt.Rectangle((j, i), 1, 1, color=color))

    ax.set_xlim(0, numVariations)
    ax.set_ylim(0, numColors)
    ax.set_xticks([])
    ax.set_yticks([])
    ax.set_aspect('equal')
    plt.show()


def avg_and_std(values):
    average = np.average(values)
    # Biased variance
    variance = np.average((values-average)**2)
    return (average, np.sqrt(variance))

def weighted_avg_and_std(values, weights):
    average = np.average(values, weights=weights)
    # Biased variance
    variance = np.average((values-average)**2, weights=weights)
    return (average, np.sqrt(variance))

def find_nearest_small_value(key, sorted_li):
    less=[i for i in sorted_li if i <= key]
    if len(less)==0:
        return 0
    else:
        return len(less)-1
    
def autocorrelation(sample):
    # Step 1: Compute the mean and standard deviation
    mean = np.mean(sample)
    std_dev = np.std(sample)
    
    # Step 2: Normalize the sample
    normalized_sample = (sample - mean) / std_dev
    
    # Step 3: Compute the autocorrelation using numpy.correlate
    autocorr = np.correlate(normalized_sample, normalized_sample, mode='full')
    
    # The result is symmetric, so we take the second half
    autocorr = autocorr[len(autocorr)//2:]
    
    # Normalize the autocorrelation values
    autocorr /= autocorr[0]
    
    return autocorr


def statsModelIndependence(values):
    result = acorr_ljungbox(values, lags=30)
    Qs=result.iloc[:,0]
    pvalues=result.iloc[:,1]
    return Qs,pvalues

def testIndependence(values,sigLevel=0.05):
    Qs,pvalues=statsModelIndependence(values)
    return all(pvalues>sigLevel)
# testIndependence(values)


def makeValuesIndependentSlow(values):
    k=0
    j=0

    testvalues=values.copy()

    while not testIndependence(testvalues):

        p=1/2**k

        random.seed(j)

        testvalues=[]

        for value in values:
            rand=random.random()
            if rand<p:
                testvalues.append(value)

        
        j+=1
        if j==3:
            k+=1
            j=0
        # assert k < 10
        
    print(f"At the end k={k}, number of samples is: {len(testvalues)}")

    return testvalues


def makeValuesIndependent(values):

    tests=3
    minK=100
    minValues=[]

    for i in range(tests):
        k=0

        testvalues=values.copy()

        while len(testvalues) > 50 and not testIndependence(testvalues):

            p=1/2
            k+=1
            random.seed(i*100+k)

            newValues=[]
            for value in testvalues:
                rand=random.random()
                if rand<p:
                    newValues.append(value)
                
            testvalues=newValues.copy()
        
        if len(testvalues) <= 50:
            continue

        if k < minK:
            minK=k
            minValues=testvalues.copy()
        
    print(f"At the end k={minK}, number of samples is: {len(minValues)}")

    return minValues
