import json
#open json file
with open('../multicore_sched/simulations/test.json') as f:
    data = json.load(f)

keys=[i for i in data.keys()]

d_vectors={}

for key in keys:
    
    d_vectors[key]={}
    vectors=data[key]['vectors']

    for a in vectors:
        print(f"{a['module']}, {a['name']}")
        values=a['value']
        mean=sum(values)/len(values)
        print(mean)

        module=a['module']
        name = a['name']

        if not module in d_vectors[key]:
            d_vectors[key][module]={}
        d_vectors[key][module][name]={}
        d_vectors[key][module][name]['time']=a['time']
        d_vectors[key][module][name]['value']=a['value']

import matplotlib.pyplot as plt


for key in d_vectors:
    time = d_vectors[key]["Computer.scheduler"]["numProcReady:vector"]["time"]
    value = d_vectors[key]["Computer.scheduler"]["numProcReady:vector"]["value"]

    # Calculate running average
    cumulative_sum = 0
    running_average = []
    for i, v in enumerate(value):
        cumulative_sum += v
        running_average.append(cumulative_sum / (i + 1) / time[i])

    # Plot original values and running average
    # plt.plot(time, value, label=f'{key} - {module} - {name} (Values)')
    plt.plot(time, running_average, label=f'{key} - {module} - {name} (Avg)')

plt.xlabel('Time')
plt.ylabel('Value')
plt.title('All Data and Running Averages')
plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
plt.tight_layout()
plt.show()