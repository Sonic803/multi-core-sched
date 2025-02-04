//
// Generated file, do not edit! Created by opp_msgtool 6.1 from msgProcess.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "msgProcess_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(MsgProcess)

MsgProcess::MsgProcess(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

MsgProcess::MsgProcess(const MsgProcess& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

MsgProcess::~MsgProcess()
{
}

MsgProcess& MsgProcess::operator=(const MsgProcess& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void MsgProcess::copy(const MsgProcess& other)
{
    this->InitDuration = other.InitDuration;
    this->IODuration = other.IODuration;
    this->finalDuration = other.finalDuration;
    this->cpuArrivalTime = other.cpuArrivalTime;
    this->readyQueueArrivalTime = other.readyQueueArrivalTime;
    this->timeWaitedInReadyQueue = other.timeWaitedInReadyQueue;
    this->isFinalPhase_ = other.isFinalPhase_;
}

void MsgProcess::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->InitDuration);
    doParsimPacking(b,this->IODuration);
    doParsimPacking(b,this->finalDuration);
    doParsimPacking(b,this->cpuArrivalTime);
    doParsimPacking(b,this->readyQueueArrivalTime);
    doParsimPacking(b,this->timeWaitedInReadyQueue);
    doParsimPacking(b,this->isFinalPhase_);
}

void MsgProcess::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->InitDuration);
    doParsimUnpacking(b,this->IODuration);
    doParsimUnpacking(b,this->finalDuration);
    doParsimUnpacking(b,this->cpuArrivalTime);
    doParsimUnpacking(b,this->readyQueueArrivalTime);
    doParsimUnpacking(b,this->timeWaitedInReadyQueue);
    doParsimUnpacking(b,this->isFinalPhase_);
}

omnetpp::simtime_t MsgProcess::getInitDuration() const
{
    return this->InitDuration;
}

void MsgProcess::setInitDuration(omnetpp::simtime_t InitDuration)
{
    this->InitDuration = InitDuration;
}

omnetpp::simtime_t MsgProcess::getIODuration() const
{
    return this->IODuration;
}

void MsgProcess::setIODuration(omnetpp::simtime_t IODuration)
{
    this->IODuration = IODuration;
}

omnetpp::simtime_t MsgProcess::getFinalDuration() const
{
    return this->finalDuration;
}

void MsgProcess::setFinalDuration(omnetpp::simtime_t finalDuration)
{
    this->finalDuration = finalDuration;
}

omnetpp::simtime_t MsgProcess::getCpuArrivalTime() const
{
    return this->cpuArrivalTime;
}

void MsgProcess::setCpuArrivalTime(omnetpp::simtime_t cpuArrivalTime)
{
    this->cpuArrivalTime = cpuArrivalTime;
}

omnetpp::simtime_t MsgProcess::getReadyQueueArrivalTime() const
{
    return this->readyQueueArrivalTime;
}

void MsgProcess::setReadyQueueArrivalTime(omnetpp::simtime_t readyQueueArrivalTime)
{
    this->readyQueueArrivalTime = readyQueueArrivalTime;
}

omnetpp::simtime_t MsgProcess::getTimeWaitedInReadyQueue() const
{
    return this->timeWaitedInReadyQueue;
}

void MsgProcess::setTimeWaitedInReadyQueue(omnetpp::simtime_t timeWaitedInReadyQueue)
{
    this->timeWaitedInReadyQueue = timeWaitedInReadyQueue;
}

bool MsgProcess::isFinalPhase() const
{
    return this->isFinalPhase_;
}

void MsgProcess::setIsFinalPhase(bool isFinalPhase)
{
    this->isFinalPhase_ = isFinalPhase;
}

class MsgProcessDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_InitDuration,
        FIELD_IODuration,
        FIELD_finalDuration,
        FIELD_cpuArrivalTime,
        FIELD_readyQueueArrivalTime,
        FIELD_timeWaitedInReadyQueue,
        FIELD_isFinalPhase,
    };
  public:
    MsgProcessDescriptor();
    virtual ~MsgProcessDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(MsgProcessDescriptor)

MsgProcessDescriptor::MsgProcessDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(MsgProcess)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

MsgProcessDescriptor::~MsgProcessDescriptor()
{
    delete[] propertyNames;
}

bool MsgProcessDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<MsgProcess *>(obj)!=nullptr;
}

const char **MsgProcessDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *MsgProcessDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int MsgProcessDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int MsgProcessDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_InitDuration
        FD_ISEDITABLE,    // FIELD_IODuration
        FD_ISEDITABLE,    // FIELD_finalDuration
        FD_ISEDITABLE,    // FIELD_cpuArrivalTime
        FD_ISEDITABLE,    // FIELD_readyQueueArrivalTime
        FD_ISEDITABLE,    // FIELD_timeWaitedInReadyQueue
        FD_ISEDITABLE,    // FIELD_isFinalPhase
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *MsgProcessDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "InitDuration",
        "IODuration",
        "finalDuration",
        "cpuArrivalTime",
        "readyQueueArrivalTime",
        "timeWaitedInReadyQueue",
        "isFinalPhase",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int MsgProcessDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "InitDuration") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "IODuration") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "finalDuration") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "cpuArrivalTime") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "readyQueueArrivalTime") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "timeWaitedInReadyQueue") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "isFinalPhase") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *MsgProcessDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "omnetpp::simtime_t",    // FIELD_InitDuration
        "omnetpp::simtime_t",    // FIELD_IODuration
        "omnetpp::simtime_t",    // FIELD_finalDuration
        "omnetpp::simtime_t",    // FIELD_cpuArrivalTime
        "omnetpp::simtime_t",    // FIELD_readyQueueArrivalTime
        "omnetpp::simtime_t",    // FIELD_timeWaitedInReadyQueue
        "bool",    // FIELD_isFinalPhase
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **MsgProcessDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *MsgProcessDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int MsgProcessDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    MsgProcess *pp = omnetpp::fromAnyPtr<MsgProcess>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void MsgProcessDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    MsgProcess *pp = omnetpp::fromAnyPtr<MsgProcess>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'MsgProcess'", field);
    }
}

const char *MsgProcessDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    MsgProcess *pp = omnetpp::fromAnyPtr<MsgProcess>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string MsgProcessDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    MsgProcess *pp = omnetpp::fromAnyPtr<MsgProcess>(object); (void)pp;
    switch (field) {
        case FIELD_InitDuration: return simtime2string(pp->getInitDuration());
        case FIELD_IODuration: return simtime2string(pp->getIODuration());
        case FIELD_finalDuration: return simtime2string(pp->getFinalDuration());
        case FIELD_cpuArrivalTime: return simtime2string(pp->getCpuArrivalTime());
        case FIELD_readyQueueArrivalTime: return simtime2string(pp->getReadyQueueArrivalTime());
        case FIELD_timeWaitedInReadyQueue: return simtime2string(pp->getTimeWaitedInReadyQueue());
        case FIELD_isFinalPhase: return bool2string(pp->isFinalPhase());
        default: return "";
    }
}

void MsgProcessDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    MsgProcess *pp = omnetpp::fromAnyPtr<MsgProcess>(object); (void)pp;
    switch (field) {
        case FIELD_InitDuration: pp->setInitDuration(string2simtime(value)); break;
        case FIELD_IODuration: pp->setIODuration(string2simtime(value)); break;
        case FIELD_finalDuration: pp->setFinalDuration(string2simtime(value)); break;
        case FIELD_cpuArrivalTime: pp->setCpuArrivalTime(string2simtime(value)); break;
        case FIELD_readyQueueArrivalTime: pp->setReadyQueueArrivalTime(string2simtime(value)); break;
        case FIELD_timeWaitedInReadyQueue: pp->setTimeWaitedInReadyQueue(string2simtime(value)); break;
        case FIELD_isFinalPhase: pp->setIsFinalPhase(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'MsgProcess'", field);
    }
}

omnetpp::cValue MsgProcessDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    MsgProcess *pp = omnetpp::fromAnyPtr<MsgProcess>(object); (void)pp;
    switch (field) {
        case FIELD_InitDuration: return pp->getInitDuration().dbl();
        case FIELD_IODuration: return pp->getIODuration().dbl();
        case FIELD_finalDuration: return pp->getFinalDuration().dbl();
        case FIELD_cpuArrivalTime: return pp->getCpuArrivalTime().dbl();
        case FIELD_readyQueueArrivalTime: return pp->getReadyQueueArrivalTime().dbl();
        case FIELD_timeWaitedInReadyQueue: return pp->getTimeWaitedInReadyQueue().dbl();
        case FIELD_isFinalPhase: return pp->isFinalPhase();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'MsgProcess' as cValue -- field index out of range?", field);
    }
}

void MsgProcessDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    MsgProcess *pp = omnetpp::fromAnyPtr<MsgProcess>(object); (void)pp;
    switch (field) {
        case FIELD_InitDuration: pp->setInitDuration(value.doubleValue()); break;
        case FIELD_IODuration: pp->setIODuration(value.doubleValue()); break;
        case FIELD_finalDuration: pp->setFinalDuration(value.doubleValue()); break;
        case FIELD_cpuArrivalTime: pp->setCpuArrivalTime(value.doubleValue()); break;
        case FIELD_readyQueueArrivalTime: pp->setReadyQueueArrivalTime(value.doubleValue()); break;
        case FIELD_timeWaitedInReadyQueue: pp->setTimeWaitedInReadyQueue(value.doubleValue()); break;
        case FIELD_isFinalPhase: pp->setIsFinalPhase(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'MsgProcess'", field);
    }
}

const char *MsgProcessDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr MsgProcessDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    MsgProcess *pp = omnetpp::fromAnyPtr<MsgProcess>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void MsgProcessDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    MsgProcess *pp = omnetpp::fromAnyPtr<MsgProcess>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'MsgProcess'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

