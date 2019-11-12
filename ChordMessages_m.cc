//
// Generated file, do not edit! Created by nedtool 5.5 from ChordMessages.msg.
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
#include "ChordMessages_m.h"

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
    for (int i=0; i<n; i++) {
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
    for (int i=0; i<n; i++) {
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
    for (int i=0; i<n; i++) {
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


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("STATE");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("STATE"));
    e->insert(PING, "PING");
    e->insert(JOIN, "JOIN");
    e->insert(FIND_SUCCESSOR, "FIND_SUCCESSOR");
    e->insert(FIND_PREDECESSOR, "FIND_PREDECESSOR");
    e->insert(NEWSUCCESSORHINT, "NEWSUCCESSORHINT");
)

Register_Class(BaseChordMessage)

BaseChordMessage::BaseChordMessage(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
}

BaseChordMessage::BaseChordMessage(const BaseChordMessage& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

BaseChordMessage::~BaseChordMessage()
{
}

BaseChordMessage& BaseChordMessage::operator=(const BaseChordMessage& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void BaseChordMessage::copy(const BaseChordMessage& other)
{
}

void BaseChordMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
}

void BaseChordMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
}

class BaseChordMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    BaseChordMessageDescriptor();
    virtual ~BaseChordMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(BaseChordMessageDescriptor)

BaseChordMessageDescriptor::BaseChordMessageDescriptor() : omnetpp::cClassDescriptor("BaseChordMessage", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

BaseChordMessageDescriptor::~BaseChordMessageDescriptor()
{
    delete[] propertynames;
}

bool BaseChordMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BaseChordMessage *>(obj)!=nullptr;
}

const char **BaseChordMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *BaseChordMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int BaseChordMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int BaseChordMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *BaseChordMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int BaseChordMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *BaseChordMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **BaseChordMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *BaseChordMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int BaseChordMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    BaseChordMessage *pp = (BaseChordMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *BaseChordMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BaseChordMessage *pp = (BaseChordMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BaseChordMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BaseChordMessage *pp = (BaseChordMessage *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool BaseChordMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    BaseChordMessage *pp = (BaseChordMessage *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *BaseChordMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *BaseChordMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    BaseChordMessage *pp = (BaseChordMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(BaseCallMessage)

BaseCallMessage::BaseCallMessage(const char *name, short kind) : ::BaseChordMessage(name,kind)
{
}

BaseCallMessage::BaseCallMessage(const BaseCallMessage& other) : ::BaseChordMessage(other)
{
    copy(other);
}

BaseCallMessage::~BaseCallMessage()
{
}

BaseCallMessage& BaseCallMessage::operator=(const BaseCallMessage& other)
{
    if (this==&other) return *this;
    ::BaseChordMessage::operator=(other);
    copy(other);
    return *this;
}

void BaseCallMessage::copy(const BaseCallMessage& other)
{
}

void BaseCallMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseChordMessage::parsimPack(b);
}

void BaseCallMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseChordMessage::parsimUnpack(b);
}

class BaseCallMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    BaseCallMessageDescriptor();
    virtual ~BaseCallMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(BaseCallMessageDescriptor)

BaseCallMessageDescriptor::BaseCallMessageDescriptor() : omnetpp::cClassDescriptor("BaseCallMessage", "BaseChordMessage")
{
    propertynames = nullptr;
}

BaseCallMessageDescriptor::~BaseCallMessageDescriptor()
{
    delete[] propertynames;
}

bool BaseCallMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BaseCallMessage *>(obj)!=nullptr;
}

const char **BaseCallMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *BaseCallMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int BaseCallMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int BaseCallMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *BaseCallMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int BaseCallMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *BaseCallMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **BaseCallMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *BaseCallMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int BaseCallMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    BaseCallMessage *pp = (BaseCallMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *BaseCallMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BaseCallMessage *pp = (BaseCallMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BaseCallMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BaseCallMessage *pp = (BaseCallMessage *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool BaseCallMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    BaseCallMessage *pp = (BaseCallMessage *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *BaseCallMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *BaseCallMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    BaseCallMessage *pp = (BaseCallMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(BaseResponseMessage)

BaseResponseMessage::BaseResponseMessage(const char *name, short kind) : ::BaseChordMessage(name,kind)
{
}

BaseResponseMessage::BaseResponseMessage(const BaseResponseMessage& other) : ::BaseChordMessage(other)
{
    copy(other);
}

BaseResponseMessage::~BaseResponseMessage()
{
}

BaseResponseMessage& BaseResponseMessage::operator=(const BaseResponseMessage& other)
{
    if (this==&other) return *this;
    ::BaseChordMessage::operator=(other);
    copy(other);
    return *this;
}

void BaseResponseMessage::copy(const BaseResponseMessage& other)
{
}

void BaseResponseMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseChordMessage::parsimPack(b);
}

void BaseResponseMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseChordMessage::parsimUnpack(b);
}

class BaseResponseMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    BaseResponseMessageDescriptor();
    virtual ~BaseResponseMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(BaseResponseMessageDescriptor)

BaseResponseMessageDescriptor::BaseResponseMessageDescriptor() : omnetpp::cClassDescriptor("BaseResponseMessage", "BaseChordMessage")
{
    propertynames = nullptr;
}

BaseResponseMessageDescriptor::~BaseResponseMessageDescriptor()
{
    delete[] propertynames;
}

bool BaseResponseMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BaseResponseMessage *>(obj)!=nullptr;
}

const char **BaseResponseMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *BaseResponseMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int BaseResponseMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int BaseResponseMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *BaseResponseMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int BaseResponseMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *BaseResponseMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **BaseResponseMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *BaseResponseMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int BaseResponseMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    BaseResponseMessage *pp = (BaseResponseMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *BaseResponseMessageDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BaseResponseMessage *pp = (BaseResponseMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BaseResponseMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BaseResponseMessage *pp = (BaseResponseMessage *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool BaseResponseMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    BaseResponseMessage *pp = (BaseResponseMessage *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *BaseResponseMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *BaseResponseMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    BaseResponseMessage *pp = (BaseResponseMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(BaseNetworkPacket)

BaseNetworkPacket::BaseNetworkPacket(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
}

BaseNetworkPacket::BaseNetworkPacket(const BaseNetworkPacket& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

BaseNetworkPacket::~BaseNetworkPacket()
{
}

BaseNetworkPacket& BaseNetworkPacket::operator=(const BaseNetworkPacket& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void BaseNetworkPacket::copy(const BaseNetworkPacket& other)
{
}

void BaseNetworkPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
}

void BaseNetworkPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
}

class BaseNetworkPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    BaseNetworkPacketDescriptor();
    virtual ~BaseNetworkPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(BaseNetworkPacketDescriptor)

BaseNetworkPacketDescriptor::BaseNetworkPacketDescriptor() : omnetpp::cClassDescriptor("BaseNetworkPacket", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

BaseNetworkPacketDescriptor::~BaseNetworkPacketDescriptor()
{
    delete[] propertynames;
}

bool BaseNetworkPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BaseNetworkPacket *>(obj)!=nullptr;
}

const char **BaseNetworkPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *BaseNetworkPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int BaseNetworkPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int BaseNetworkPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *BaseNetworkPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int BaseNetworkPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *BaseNetworkPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **BaseNetworkPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *BaseNetworkPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int BaseNetworkPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    BaseNetworkPacket *pp = (BaseNetworkPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *BaseNetworkPacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BaseNetworkPacket *pp = (BaseNetworkPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BaseNetworkPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BaseNetworkPacket *pp = (BaseNetworkPacket *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool BaseNetworkPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    BaseNetworkPacket *pp = (BaseNetworkPacket *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *BaseNetworkPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *BaseNetworkPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    BaseNetworkPacket *pp = (BaseNetworkPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(Stabilization)

Stabilization::Stabilization(const char *name, short kind) : ::BaseNetworkPacket(name,kind)
{
    ring_arraysize = 0;
    this->ring = 0;
    this->hops = 0;
    this->start = 0;
}

Stabilization::Stabilization(const Stabilization& other) : ::BaseNetworkPacket(other)
{
    ring_arraysize = 0;
    this->ring = 0;
    copy(other);
}

Stabilization::~Stabilization()
{
    delete [] this->ring;
}

Stabilization& Stabilization::operator=(const Stabilization& other)
{
    if (this==&other) return *this;
    ::BaseNetworkPacket::operator=(other);
    copy(other);
    return *this;
}

void Stabilization::copy(const Stabilization& other)
{
    delete [] this->ring;
    this->ring = (other.ring_arraysize==0) ? nullptr : new ::omnetpp::opp_string[other.ring_arraysize];
    ring_arraysize = other.ring_arraysize;
    for (unsigned int i=0; i<ring_arraysize; i++)
        this->ring[i] = other.ring[i];
    this->src = other.src;
    this->hops = other.hops;
    this->start = other.start;
}

void Stabilization::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseNetworkPacket::parsimPack(b);
    b->pack(ring_arraysize);
    doParsimArrayPacking(b,this->ring,ring_arraysize);
    doParsimPacking(b,this->src);
    doParsimPacking(b,this->hops);
    doParsimPacking(b,this->start);
}

void Stabilization::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseNetworkPacket::parsimUnpack(b);
    delete [] this->ring;
    b->unpack(ring_arraysize);
    if (ring_arraysize==0) {
        this->ring = 0;
    } else {
        this->ring = new ::omnetpp::opp_string[ring_arraysize];
        doParsimArrayUnpacking(b,this->ring,ring_arraysize);
    }
    doParsimUnpacking(b,this->src);
    doParsimUnpacking(b,this->hops);
    doParsimUnpacking(b,this->start);
}

void Stabilization::setRingArraySize(unsigned int size)
{
    ::omnetpp::opp_string *ring2 = (size==0) ? nullptr : new ::omnetpp::opp_string[size];
    unsigned int sz = ring_arraysize < size ? ring_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        ring2[i] = this->ring[i];
    for (unsigned int i=sz; i<size; i++)
        ring2[i] = 0;
    ring_arraysize = size;
    delete [] this->ring;
    this->ring = ring2;
}

unsigned int Stabilization::getRingArraySize() const
{
    return ring_arraysize;
}

const char * Stabilization::getRing(unsigned int k) const
{
    if (k>=ring_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", ring_arraysize, k);
    return this->ring[k].c_str();
}

void Stabilization::setRing(unsigned int k, const char * ring)
{
    if (k>=ring_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", ring_arraysize, k);
    this->ring[k] = ring;
}

const char * Stabilization::getSrc() const
{
    return this->src.c_str();
}

void Stabilization::setSrc(const char * src)
{
    this->src = src;
}

int Stabilization::getHops() const
{
    return this->hops;
}

void Stabilization::setHops(int hops)
{
    this->hops = hops;
}

::omnetpp::simtime_t Stabilization::getStart() const
{
    return this->start;
}

void Stabilization::setStart(::omnetpp::simtime_t start)
{
    this->start = start;
}

class StabilizationDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    StabilizationDescriptor();
    virtual ~StabilizationDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(StabilizationDescriptor)

StabilizationDescriptor::StabilizationDescriptor() : omnetpp::cClassDescriptor("Stabilization", "BaseNetworkPacket")
{
    propertynames = nullptr;
}

StabilizationDescriptor::~StabilizationDescriptor()
{
    delete[] propertynames;
}

bool StabilizationDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Stabilization *>(obj)!=nullptr;
}

const char **StabilizationDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *StabilizationDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int StabilizationDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int StabilizationDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *StabilizationDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ring",
        "src",
        "hops",
        "start",
    };
    return (field>=0 && field<4) ? fieldNames[field] : nullptr;
}

int StabilizationDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "ring")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+1;
    if (fieldName[0]=='h' && strcmp(fieldName, "hops")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "start")==0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *StabilizationDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "string",
        "int",
        "simtime_t",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : nullptr;
}

const char **StabilizationDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *StabilizationDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int StabilizationDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Stabilization *pp = (Stabilization *)object; (void)pp;
    switch (field) {
        case 0: return pp->getRingArraySize();
        default: return 0;
    }
}

const char *StabilizationDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Stabilization *pp = (Stabilization *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string StabilizationDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Stabilization *pp = (Stabilization *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getRing(i));
        case 1: return oppstring2string(pp->getSrc());
        case 2: return long2string(pp->getHops());
        case 3: return simtime2string(pp->getStart());
        default: return "";
    }
}

bool StabilizationDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Stabilization *pp = (Stabilization *)object; (void)pp;
    switch (field) {
        case 0: pp->setRing(i,(value)); return true;
        case 1: pp->setSrc((value)); return true;
        case 2: pp->setHops(string2long(value)); return true;
        case 3: pp->setStart(string2simtime(value)); return true;
        default: return false;
    }
}

const char *StabilizationDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *StabilizationDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Stabilization *pp = (Stabilization *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(PingTimeout)

PingTimeout::PingTimeout(const char *name, short kind) : ::BaseChordMessage(name,kind)
{
}

PingTimeout::PingTimeout(const PingTimeout& other) : ::BaseChordMessage(other)
{
    copy(other);
}

PingTimeout::~PingTimeout()
{
}

PingTimeout& PingTimeout::operator=(const PingTimeout& other)
{
    if (this==&other) return *this;
    ::BaseChordMessage::operator=(other);
    copy(other);
    return *this;
}

void PingTimeout::copy(const PingTimeout& other)
{
    this->failed = other.failed;
}

void PingTimeout::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseChordMessage::parsimPack(b);
    doParsimPacking(b,this->failed);
}

void PingTimeout::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseChordMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->failed);
}

const char * PingTimeout::getFailed() const
{
    return this->failed.c_str();
}

void PingTimeout::setFailed(const char * failed)
{
    this->failed = failed;
}

class PingTimeoutDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    PingTimeoutDescriptor();
    virtual ~PingTimeoutDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(PingTimeoutDescriptor)

PingTimeoutDescriptor::PingTimeoutDescriptor() : omnetpp::cClassDescriptor("PingTimeout", "BaseChordMessage")
{
    propertynames = nullptr;
}

PingTimeoutDescriptor::~PingTimeoutDescriptor()
{
    delete[] propertynames;
}

bool PingTimeoutDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PingTimeout *>(obj)!=nullptr;
}

const char **PingTimeoutDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *PingTimeoutDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int PingTimeoutDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int PingTimeoutDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *PingTimeoutDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "failed",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int PingTimeoutDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "failed")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *PingTimeoutDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **PingTimeoutDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *PingTimeoutDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int PingTimeoutDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    PingTimeout *pp = (PingTimeout *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *PingTimeoutDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    PingTimeout *pp = (PingTimeout *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PingTimeoutDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    PingTimeout *pp = (PingTimeout *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getFailed());
        default: return "";
    }
}

bool PingTimeoutDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    PingTimeout *pp = (PingTimeout *)object; (void)pp;
    switch (field) {
        case 0: pp->setFailed((value)); return true;
        default: return false;
    }
}

const char *PingTimeoutDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *PingTimeoutDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    PingTimeout *pp = (PingTimeout *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(PingCall)

PingCall::PingCall(const char *name, short kind) : ::BaseCallMessage(name,kind)
{
}

PingCall::PingCall(const PingCall& other) : ::BaseCallMessage(other)
{
    copy(other);
}

PingCall::~PingCall()
{
}

PingCall& PingCall::operator=(const PingCall& other)
{
    if (this==&other) return *this;
    ::BaseCallMessage::operator=(other);
    copy(other);
    return *this;
}

void PingCall::copy(const PingCall& other)
{
}

void PingCall::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseCallMessage::parsimPack(b);
}

void PingCall::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseCallMessage::parsimUnpack(b);
}

class PingCallDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    PingCallDescriptor();
    virtual ~PingCallDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(PingCallDescriptor)

PingCallDescriptor::PingCallDescriptor() : omnetpp::cClassDescriptor("PingCall", "BaseCallMessage")
{
    propertynames = nullptr;
}

PingCallDescriptor::~PingCallDescriptor()
{
    delete[] propertynames;
}

bool PingCallDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PingCall *>(obj)!=nullptr;
}

const char **PingCallDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *PingCallDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int PingCallDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int PingCallDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *PingCallDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int PingCallDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *PingCallDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **PingCallDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *PingCallDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int PingCallDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    PingCall *pp = (PingCall *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *PingCallDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    PingCall *pp = (PingCall *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PingCallDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    PingCall *pp = (PingCall *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool PingCallDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    PingCall *pp = (PingCall *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *PingCallDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *PingCallDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    PingCall *pp = (PingCall *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(PingResponse)

PingResponse::PingResponse(const char *name, short kind) : ::BaseResponseMessage(name,kind)
{
}

PingResponse::PingResponse(const PingResponse& other) : ::BaseResponseMessage(other)
{
    copy(other);
}

PingResponse::~PingResponse()
{
}

PingResponse& PingResponse::operator=(const PingResponse& other)
{
    if (this==&other) return *this;
    ::BaseResponseMessage::operator=(other);
    copy(other);
    return *this;
}

void PingResponse::copy(const PingResponse& other)
{
}

void PingResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseResponseMessage::parsimPack(b);
}

void PingResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseResponseMessage::parsimUnpack(b);
}

class PingResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    PingResponseDescriptor();
    virtual ~PingResponseDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(PingResponseDescriptor)

PingResponseDescriptor::PingResponseDescriptor() : omnetpp::cClassDescriptor("PingResponse", "BaseResponseMessage")
{
    propertynames = nullptr;
}

PingResponseDescriptor::~PingResponseDescriptor()
{
    delete[] propertynames;
}

bool PingResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PingResponse *>(obj)!=nullptr;
}

const char **PingResponseDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *PingResponseDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int PingResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int PingResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *PingResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int PingResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *PingResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **PingResponseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *PingResponseDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int PingResponseDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    PingResponse *pp = (PingResponse *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *PingResponseDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    PingResponse *pp = (PingResponse *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PingResponseDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    PingResponse *pp = (PingResponse *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool PingResponseDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    PingResponse *pp = (PingResponse *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *PingResponseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *PingResponseDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    PingResponse *pp = (PingResponse *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(JoinCall)

JoinCall::JoinCall(const char *name, short kind) : ::BaseCallMessage(name,kind)
{
}

JoinCall::JoinCall(const JoinCall& other) : ::BaseCallMessage(other)
{
    copy(other);
}

JoinCall::~JoinCall()
{
}

JoinCall& JoinCall::operator=(const JoinCall& other)
{
    if (this==&other) return *this;
    ::BaseCallMessage::operator=(other);
    copy(other);
    return *this;
}

void JoinCall::copy(const JoinCall& other)
{
    this->requester = other.requester;
    this->key = other.key;
}

void JoinCall::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseCallMessage::parsimPack(b);
    doParsimPacking(b,this->requester);
    doParsimPacking(b,this->key);
}

void JoinCall::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseCallMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->requester);
    doParsimUnpacking(b,this->key);
}

const char * JoinCall::getRequester() const
{
    return this->requester.c_str();
}

void JoinCall::setRequester(const char * requester)
{
    this->requester = requester;
}

const char * JoinCall::getKey() const
{
    return this->key.c_str();
}

void JoinCall::setKey(const char * key)
{
    this->key = key;
}

class JoinCallDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    JoinCallDescriptor();
    virtual ~JoinCallDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(JoinCallDescriptor)

JoinCallDescriptor::JoinCallDescriptor() : omnetpp::cClassDescriptor("JoinCall", "BaseCallMessage")
{
    propertynames = nullptr;
}

JoinCallDescriptor::~JoinCallDescriptor()
{
    delete[] propertynames;
}

bool JoinCallDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<JoinCall *>(obj)!=nullptr;
}

const char **JoinCallDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *JoinCallDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int JoinCallDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int JoinCallDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *JoinCallDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "requester",
        "key",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int JoinCallDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "requester")==0) return base+0;
    if (fieldName[0]=='k' && strcmp(fieldName, "key")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *JoinCallDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "string",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **JoinCallDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *JoinCallDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int JoinCallDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    JoinCall *pp = (JoinCall *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *JoinCallDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    JoinCall *pp = (JoinCall *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string JoinCallDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    JoinCall *pp = (JoinCall *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getRequester());
        case 1: return oppstring2string(pp->getKey());
        default: return "";
    }
}

bool JoinCallDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    JoinCall *pp = (JoinCall *)object; (void)pp;
    switch (field) {
        case 0: pp->setRequester((value)); return true;
        case 1: pp->setKey((value)); return true;
        default: return false;
    }
}

const char *JoinCallDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *JoinCallDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    JoinCall *pp = (JoinCall *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(JoinResponse)

JoinResponse::JoinResponse(const char *name, short kind) : ::BaseResponseMessage(name,kind)
{
    this->successorNum = 0;
    successorNode_arraysize = 0;
    this->successorNode = 0;
}

JoinResponse::JoinResponse(const JoinResponse& other) : ::BaseResponseMessage(other)
{
    successorNode_arraysize = 0;
    this->successorNode = 0;
    copy(other);
}

JoinResponse::~JoinResponse()
{
    delete [] this->successorNode;
}

JoinResponse& JoinResponse::operator=(const JoinResponse& other)
{
    if (this==&other) return *this;
    ::BaseResponseMessage::operator=(other);
    copy(other);
    return *this;
}

void JoinResponse::copy(const JoinResponse& other)
{
    this->successorNum = other.successorNum;
    this->src = other.src;
    delete [] this->successorNode;
    this->successorNode = (other.successorNode_arraysize==0) ? nullptr : new ::omnetpp::opp_string[other.successorNode_arraysize];
    successorNode_arraysize = other.successorNode_arraysize;
    for (unsigned int i=0; i<successorNode_arraysize; i++)
        this->successorNode[i] = other.successorNode[i];
    this->predecessorNode = other.predecessorNode;
}

void JoinResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseResponseMessage::parsimPack(b);
    doParsimPacking(b,this->successorNum);
    doParsimPacking(b,this->src);
    b->pack(successorNode_arraysize);
    doParsimArrayPacking(b,this->successorNode,successorNode_arraysize);
    doParsimPacking(b,this->predecessorNode);
}

void JoinResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseResponseMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->successorNum);
    doParsimUnpacking(b,this->src);
    delete [] this->successorNode;
    b->unpack(successorNode_arraysize);
    if (successorNode_arraysize==0) {
        this->successorNode = 0;
    } else {
        this->successorNode = new ::omnetpp::opp_string[successorNode_arraysize];
        doParsimArrayUnpacking(b,this->successorNode,successorNode_arraysize);
    }
    doParsimUnpacking(b,this->predecessorNode);
}

int JoinResponse::getSuccessorNum() const
{
    return this->successorNum;
}

void JoinResponse::setSuccessorNum(int successorNum)
{
    this->successorNum = successorNum;
}

const char * JoinResponse::getSrc() const
{
    return this->src.c_str();
}

void JoinResponse::setSrc(const char * src)
{
    this->src = src;
}

void JoinResponse::setSuccessorNodeArraySize(unsigned int size)
{
    ::omnetpp::opp_string *successorNode2 = (size==0) ? nullptr : new ::omnetpp::opp_string[size];
    unsigned int sz = successorNode_arraysize < size ? successorNode_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        successorNode2[i] = this->successorNode[i];
    for (unsigned int i=sz; i<size; i++)
        successorNode2[i] = 0;
    successorNode_arraysize = size;
    delete [] this->successorNode;
    this->successorNode = successorNode2;
}

unsigned int JoinResponse::getSuccessorNodeArraySize() const
{
    return successorNode_arraysize;
}

const char * JoinResponse::getSuccessorNode(unsigned int k) const
{
    if (k>=successorNode_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", successorNode_arraysize, k);
    return this->successorNode[k].c_str();
}

void JoinResponse::setSuccessorNode(unsigned int k, const char * successorNode)
{
    if (k>=successorNode_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", successorNode_arraysize, k);
    this->successorNode[k] = successorNode;
}

const char * JoinResponse::getPredecessorNode() const
{
    return this->predecessorNode.c_str();
}

void JoinResponse::setPredecessorNode(const char * predecessorNode)
{
    this->predecessorNode = predecessorNode;
}

class JoinResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    JoinResponseDescriptor();
    virtual ~JoinResponseDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(JoinResponseDescriptor)

JoinResponseDescriptor::JoinResponseDescriptor() : omnetpp::cClassDescriptor("JoinResponse", "BaseResponseMessage")
{
    propertynames = nullptr;
}

JoinResponseDescriptor::~JoinResponseDescriptor()
{
    delete[] propertynames;
}

bool JoinResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<JoinResponse *>(obj)!=nullptr;
}

const char **JoinResponseDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *JoinResponseDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int JoinResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int JoinResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *JoinResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "successorNum",
        "src",
        "successorNode",
        "predecessorNode",
    };
    return (field>=0 && field<4) ? fieldNames[field] : nullptr;
}

int JoinResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "successorNum")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "successorNode")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "predecessorNode")==0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *JoinResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "string",
        "string",
        "string",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : nullptr;
}

const char **JoinResponseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *JoinResponseDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int JoinResponseDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    JoinResponse *pp = (JoinResponse *)object; (void)pp;
    switch (field) {
        case 2: return pp->getSuccessorNodeArraySize();
        default: return 0;
    }
}

const char *JoinResponseDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    JoinResponse *pp = (JoinResponse *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string JoinResponseDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    JoinResponse *pp = (JoinResponse *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSuccessorNum());
        case 1: return oppstring2string(pp->getSrc());
        case 2: return oppstring2string(pp->getSuccessorNode(i));
        case 3: return oppstring2string(pp->getPredecessorNode());
        default: return "";
    }
}

bool JoinResponseDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    JoinResponse *pp = (JoinResponse *)object; (void)pp;
    switch (field) {
        case 0: pp->setSuccessorNum(string2long(value)); return true;
        case 1: pp->setSrc((value)); return true;
        case 2: pp->setSuccessorNode(i,(value)); return true;
        case 3: pp->setPredecessorNode((value)); return true;
        default: return false;
    }
}

const char *JoinResponseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *JoinResponseDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    JoinResponse *pp = (JoinResponse *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(StabilizeCall)

StabilizeCall::StabilizeCall(const char *name, short kind) : ::BaseCallMessage(name,kind)
{
}

StabilizeCall::StabilizeCall(const StabilizeCall& other) : ::BaseCallMessage(other)
{
    copy(other);
}

StabilizeCall::~StabilizeCall()
{
}

StabilizeCall& StabilizeCall::operator=(const StabilizeCall& other)
{
    if (this==&other) return *this;
    ::BaseCallMessage::operator=(other);
    copy(other);
    return *this;
}

void StabilizeCall::copy(const StabilizeCall& other)
{
}

void StabilizeCall::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseCallMessage::parsimPack(b);
}

void StabilizeCall::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseCallMessage::parsimUnpack(b);
}

class StabilizeCallDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    StabilizeCallDescriptor();
    virtual ~StabilizeCallDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(StabilizeCallDescriptor)

StabilizeCallDescriptor::StabilizeCallDescriptor() : omnetpp::cClassDescriptor("StabilizeCall", "BaseCallMessage")
{
    propertynames = nullptr;
}

StabilizeCallDescriptor::~StabilizeCallDescriptor()
{
    delete[] propertynames;
}

bool StabilizeCallDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<StabilizeCall *>(obj)!=nullptr;
}

const char **StabilizeCallDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *StabilizeCallDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int StabilizeCallDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int StabilizeCallDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *StabilizeCallDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int StabilizeCallDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *StabilizeCallDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **StabilizeCallDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *StabilizeCallDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int StabilizeCallDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    StabilizeCall *pp = (StabilizeCall *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *StabilizeCallDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    StabilizeCall *pp = (StabilizeCall *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string StabilizeCallDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    StabilizeCall *pp = (StabilizeCall *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool StabilizeCallDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    StabilizeCall *pp = (StabilizeCall *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *StabilizeCallDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *StabilizeCallDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    StabilizeCall *pp = (StabilizeCall *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(StabilizeResponse)

StabilizeResponse::StabilizeResponse(const char *name, short kind) : ::BaseResponseMessage(name,kind)
{
}

StabilizeResponse::StabilizeResponse(const StabilizeResponse& other) : ::BaseResponseMessage(other)
{
    copy(other);
}

StabilizeResponse::~StabilizeResponse()
{
}

StabilizeResponse& StabilizeResponse::operator=(const StabilizeResponse& other)
{
    if (this==&other) return *this;
    ::BaseResponseMessage::operator=(other);
    copy(other);
    return *this;
}

void StabilizeResponse::copy(const StabilizeResponse& other)
{
    this->predecessorNode = other.predecessorNode;
    this->predecessorNodeIP = other.predecessorNodeIP;
}

void StabilizeResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseResponseMessage::parsimPack(b);
    doParsimPacking(b,this->predecessorNode);
    doParsimPacking(b,this->predecessorNodeIP);
}

void StabilizeResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseResponseMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->predecessorNode);
    doParsimUnpacking(b,this->predecessorNodeIP);
}

const char * StabilizeResponse::getPredecessorNode() const
{
    return this->predecessorNode.c_str();
}

void StabilizeResponse::setPredecessorNode(const char * predecessorNode)
{
    this->predecessorNode = predecessorNode;
}

const char * StabilizeResponse::getPredecessorNodeIP() const
{
    return this->predecessorNodeIP.c_str();
}

void StabilizeResponse::setPredecessorNodeIP(const char * predecessorNodeIP)
{
    this->predecessorNodeIP = predecessorNodeIP;
}

class StabilizeResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    StabilizeResponseDescriptor();
    virtual ~StabilizeResponseDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(StabilizeResponseDescriptor)

StabilizeResponseDescriptor::StabilizeResponseDescriptor() : omnetpp::cClassDescriptor("StabilizeResponse", "BaseResponseMessage")
{
    propertynames = nullptr;
}

StabilizeResponseDescriptor::~StabilizeResponseDescriptor()
{
    delete[] propertynames;
}

bool StabilizeResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<StabilizeResponse *>(obj)!=nullptr;
}

const char **StabilizeResponseDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *StabilizeResponseDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int StabilizeResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int StabilizeResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *StabilizeResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "predecessorNode",
        "predecessorNodeIP",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int StabilizeResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "predecessorNode")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "predecessorNodeIP")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *StabilizeResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "string",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **StabilizeResponseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *StabilizeResponseDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int StabilizeResponseDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    StabilizeResponse *pp = (StabilizeResponse *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *StabilizeResponseDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    StabilizeResponse *pp = (StabilizeResponse *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string StabilizeResponseDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    StabilizeResponse *pp = (StabilizeResponse *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getPredecessorNode());
        case 1: return oppstring2string(pp->getPredecessorNodeIP());
        default: return "";
    }
}

bool StabilizeResponseDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    StabilizeResponse *pp = (StabilizeResponse *)object; (void)pp;
    switch (field) {
        case 0: pp->setPredecessorNode((value)); return true;
        case 1: pp->setPredecessorNodeIP((value)); return true;
        default: return false;
    }
}

const char *StabilizeResponseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *StabilizeResponseDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    StabilizeResponse *pp = (StabilizeResponse *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NotifyCall)

NotifyCall::NotifyCall(const char *name, short kind) : ::BaseCallMessage(name,kind)
{
}

NotifyCall::NotifyCall(const NotifyCall& other) : ::BaseCallMessage(other)
{
    copy(other);
}

NotifyCall::~NotifyCall()
{
}

NotifyCall& NotifyCall::operator=(const NotifyCall& other)
{
    if (this==&other) return *this;
    ::BaseCallMessage::operator=(other);
    copy(other);
    return *this;
}

void NotifyCall::copy(const NotifyCall& other)
{
    this->failed = other.failed;
}

void NotifyCall::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseCallMessage::parsimPack(b);
    doParsimPacking(b,this->failed);
}

void NotifyCall::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseCallMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->failed);
}

const char * NotifyCall::getFailed() const
{
    return this->failed.c_str();
}

void NotifyCall::setFailed(const char * failed)
{
    this->failed = failed;
}

class NotifyCallDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NotifyCallDescriptor();
    virtual ~NotifyCallDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(NotifyCallDescriptor)

NotifyCallDescriptor::NotifyCallDescriptor() : omnetpp::cClassDescriptor("NotifyCall", "BaseCallMessage")
{
    propertynames = nullptr;
}

NotifyCallDescriptor::~NotifyCallDescriptor()
{
    delete[] propertynames;
}

bool NotifyCallDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NotifyCall *>(obj)!=nullptr;
}

const char **NotifyCallDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NotifyCallDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NotifyCallDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int NotifyCallDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *NotifyCallDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "failed",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int NotifyCallDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "failed")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NotifyCallDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **NotifyCallDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *NotifyCallDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int NotifyCallDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NotifyCall *pp = (NotifyCall *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NotifyCallDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NotifyCall *pp = (NotifyCall *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NotifyCallDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NotifyCall *pp = (NotifyCall *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getFailed());
        default: return "";
    }
}

bool NotifyCallDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NotifyCall *pp = (NotifyCall *)object; (void)pp;
    switch (field) {
        case 0: pp->setFailed((value)); return true;
        default: return false;
    }
}

const char *NotifyCallDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *NotifyCallDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NotifyCall *pp = (NotifyCall *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NotifyResponse)

NotifyResponse::NotifyResponse(const char *name, short kind) : ::BaseResponseMessage(name,kind)
{
    this->successorNum = 0;
    successorNode_arraysize = 0;
    this->successorNode = 0;
}

NotifyResponse::NotifyResponse(const NotifyResponse& other) : ::BaseResponseMessage(other)
{
    successorNode_arraysize = 0;
    this->successorNode = 0;
    copy(other);
}

NotifyResponse::~NotifyResponse()
{
    delete [] this->successorNode;
}

NotifyResponse& NotifyResponse::operator=(const NotifyResponse& other)
{
    if (this==&other) return *this;
    ::BaseResponseMessage::operator=(other);
    copy(other);
    return *this;
}

void NotifyResponse::copy(const NotifyResponse& other)
{
    this->successorNum = other.successorNum;
    delete [] this->successorNode;
    this->successorNode = (other.successorNode_arraysize==0) ? nullptr : new ::omnetpp::opp_string[other.successorNode_arraysize];
    successorNode_arraysize = other.successorNode_arraysize;
    for (unsigned int i=0; i<successorNode_arraysize; i++)
        this->successorNode[i] = other.successorNode[i];
}

void NotifyResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseResponseMessage::parsimPack(b);
    doParsimPacking(b,this->successorNum);
    b->pack(successorNode_arraysize);
    doParsimArrayPacking(b,this->successorNode,successorNode_arraysize);
}

void NotifyResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseResponseMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->successorNum);
    delete [] this->successorNode;
    b->unpack(successorNode_arraysize);
    if (successorNode_arraysize==0) {
        this->successorNode = 0;
    } else {
        this->successorNode = new ::omnetpp::opp_string[successorNode_arraysize];
        doParsimArrayUnpacking(b,this->successorNode,successorNode_arraysize);
    }
}

int NotifyResponse::getSuccessorNum() const
{
    return this->successorNum;
}

void NotifyResponse::setSuccessorNum(int successorNum)
{
    this->successorNum = successorNum;
}

void NotifyResponse::setSuccessorNodeArraySize(unsigned int size)
{
    ::omnetpp::opp_string *successorNode2 = (size==0) ? nullptr : new ::omnetpp::opp_string[size];
    unsigned int sz = successorNode_arraysize < size ? successorNode_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        successorNode2[i] = this->successorNode[i];
    for (unsigned int i=sz; i<size; i++)
        successorNode2[i] = 0;
    successorNode_arraysize = size;
    delete [] this->successorNode;
    this->successorNode = successorNode2;
}

unsigned int NotifyResponse::getSuccessorNodeArraySize() const
{
    return successorNode_arraysize;
}

const char * NotifyResponse::getSuccessorNode(unsigned int k) const
{
    if (k>=successorNode_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", successorNode_arraysize, k);
    return this->successorNode[k].c_str();
}

void NotifyResponse::setSuccessorNode(unsigned int k, const char * successorNode)
{
    if (k>=successorNode_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", successorNode_arraysize, k);
    this->successorNode[k] = successorNode;
}

class NotifyResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NotifyResponseDescriptor();
    virtual ~NotifyResponseDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(NotifyResponseDescriptor)

NotifyResponseDescriptor::NotifyResponseDescriptor() : omnetpp::cClassDescriptor("NotifyResponse", "BaseResponseMessage")
{
    propertynames = nullptr;
}

NotifyResponseDescriptor::~NotifyResponseDescriptor()
{
    delete[] propertynames;
}

bool NotifyResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NotifyResponse *>(obj)!=nullptr;
}

const char **NotifyResponseDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NotifyResponseDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NotifyResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int NotifyResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *NotifyResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "successorNum",
        "successorNode",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int NotifyResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "successorNum")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "successorNode")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NotifyResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "string",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **NotifyResponseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *NotifyResponseDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int NotifyResponseDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NotifyResponse *pp = (NotifyResponse *)object; (void)pp;
    switch (field) {
        case 1: return pp->getSuccessorNodeArraySize();
        default: return 0;
    }
}

const char *NotifyResponseDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NotifyResponse *pp = (NotifyResponse *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NotifyResponseDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NotifyResponse *pp = (NotifyResponse *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSuccessorNum());
        case 1: return oppstring2string(pp->getSuccessorNode(i));
        default: return "";
    }
}

bool NotifyResponseDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NotifyResponse *pp = (NotifyResponse *)object; (void)pp;
    switch (field) {
        case 0: pp->setSuccessorNum(string2long(value)); return true;
        case 1: pp->setSuccessorNode(i,(value)); return true;
        default: return false;
    }
}

const char *NotifyResponseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *NotifyResponseDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NotifyResponse *pp = (NotifyResponse *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(FixFingerCall)

FixFingerCall::FixFingerCall(const char *name, short kind) : ::BaseCallMessage(name,kind)
{
    this->finger = 0;
}

FixFingerCall::FixFingerCall(const FixFingerCall& other) : ::BaseCallMessage(other)
{
    copy(other);
}

FixFingerCall::~FixFingerCall()
{
}

FixFingerCall& FixFingerCall::operator=(const FixFingerCall& other)
{
    if (this==&other) return *this;
    ::BaseCallMessage::operator=(other);
    copy(other);
    return *this;
}

void FixFingerCall::copy(const FixFingerCall& other)
{
    this->finger = other.finger;
    this->fingerKey = other.fingerKey;
    this->requester = other.requester;
}

void FixFingerCall::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseCallMessage::parsimPack(b);
    doParsimPacking(b,this->finger);
    doParsimPacking(b,this->fingerKey);
    doParsimPacking(b,this->requester);
}

void FixFingerCall::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseCallMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->finger);
    doParsimUnpacking(b,this->fingerKey);
    doParsimUnpacking(b,this->requester);
}

int FixFingerCall::getFinger() const
{
    return this->finger;
}

void FixFingerCall::setFinger(int finger)
{
    this->finger = finger;
}

const char * FixFingerCall::getFingerKey() const
{
    return this->fingerKey.c_str();
}

void FixFingerCall::setFingerKey(const char * fingerKey)
{
    this->fingerKey = fingerKey;
}

const char * FixFingerCall::getRequester() const
{
    return this->requester.c_str();
}

void FixFingerCall::setRequester(const char * requester)
{
    this->requester = requester;
}

class FixFingerCallDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    FixFingerCallDescriptor();
    virtual ~FixFingerCallDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(FixFingerCallDescriptor)

FixFingerCallDescriptor::FixFingerCallDescriptor() : omnetpp::cClassDescriptor("FixFingerCall", "BaseCallMessage")
{
    propertynames = nullptr;
}

FixFingerCallDescriptor::~FixFingerCallDescriptor()
{
    delete[] propertynames;
}

bool FixFingerCallDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FixFingerCall *>(obj)!=nullptr;
}

const char **FixFingerCallDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *FixFingerCallDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int FixFingerCallDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int FixFingerCallDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *FixFingerCallDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "finger",
        "fingerKey",
        "requester",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int FixFingerCallDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "finger")==0) return base+0;
    if (fieldName[0]=='f' && strcmp(fieldName, "fingerKey")==0) return base+1;
    if (fieldName[0]=='r' && strcmp(fieldName, "requester")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *FixFingerCallDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "string",
        "string",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **FixFingerCallDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *FixFingerCallDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int FixFingerCallDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    FixFingerCall *pp = (FixFingerCall *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *FixFingerCallDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FixFingerCall *pp = (FixFingerCall *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FixFingerCallDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FixFingerCall *pp = (FixFingerCall *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getFinger());
        case 1: return oppstring2string(pp->getFingerKey());
        case 2: return oppstring2string(pp->getRequester());
        default: return "";
    }
}

bool FixFingerCallDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    FixFingerCall *pp = (FixFingerCall *)object; (void)pp;
    switch (field) {
        case 0: pp->setFinger(string2long(value)); return true;
        case 1: pp->setFingerKey((value)); return true;
        case 2: pp->setRequester((value)); return true;
        default: return false;
    }
}

const char *FixFingerCallDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *FixFingerCallDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    FixFingerCall *pp = (FixFingerCall *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(FixFingerResponse)

FixFingerResponse::FixFingerResponse(const char *name, short kind) : ::BaseResponseMessage(name,kind)
{
    this->finger = 0;
}

FixFingerResponse::FixFingerResponse(const FixFingerResponse& other) : ::BaseResponseMessage(other)
{
    copy(other);
}

FixFingerResponse::~FixFingerResponse()
{
}

FixFingerResponse& FixFingerResponse::operator=(const FixFingerResponse& other)
{
    if (this==&other) return *this;
    ::BaseResponseMessage::operator=(other);
    copy(other);
    return *this;
}

void FixFingerResponse::copy(const FixFingerResponse& other)
{
    this->finger = other.finger;
    this->successorNode = other.successorNode;
}

void FixFingerResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseResponseMessage::parsimPack(b);
    doParsimPacking(b,this->finger);
    doParsimPacking(b,this->successorNode);
}

void FixFingerResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseResponseMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->finger);
    doParsimUnpacking(b,this->successorNode);
}

int FixFingerResponse::getFinger() const
{
    return this->finger;
}

void FixFingerResponse::setFinger(int finger)
{
    this->finger = finger;
}

const char * FixFingerResponse::getSuccessorNode() const
{
    return this->successorNode.c_str();
}

void FixFingerResponse::setSuccessorNode(const char * successorNode)
{
    this->successorNode = successorNode;
}

class FixFingerResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    FixFingerResponseDescriptor();
    virtual ~FixFingerResponseDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(FixFingerResponseDescriptor)

FixFingerResponseDescriptor::FixFingerResponseDescriptor() : omnetpp::cClassDescriptor("FixFingerResponse", "BaseResponseMessage")
{
    propertynames = nullptr;
}

FixFingerResponseDescriptor::~FixFingerResponseDescriptor()
{
    delete[] propertynames;
}

bool FixFingerResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FixFingerResponse *>(obj)!=nullptr;
}

const char **FixFingerResponseDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *FixFingerResponseDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int FixFingerResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int FixFingerResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *FixFingerResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "finger",
        "successorNode",
    };
    return (field>=0 && field<2) ? fieldNames[field] : nullptr;
}

int FixFingerResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "finger")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "successorNode")==0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *FixFingerResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "string",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : nullptr;
}

const char **FixFingerResponseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *FixFingerResponseDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int FixFingerResponseDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    FixFingerResponse *pp = (FixFingerResponse *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *FixFingerResponseDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FixFingerResponse *pp = (FixFingerResponse *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FixFingerResponseDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FixFingerResponse *pp = (FixFingerResponse *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getFinger());
        case 1: return oppstring2string(pp->getSuccessorNode());
        default: return "";
    }
}

bool FixFingerResponseDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    FixFingerResponse *pp = (FixFingerResponse *)object; (void)pp;
    switch (field) {
        case 0: pp->setFinger(string2long(value)); return true;
        case 1: pp->setSuccessorNode((value)); return true;
        default: return false;
    }
}

const char *FixFingerResponseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *FixFingerResponseDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    FixFingerResponse *pp = (FixFingerResponse *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NotifyBoostrapList)

NotifyBoostrapList::NotifyBoostrapList(const char *name, short kind) : ::BaseNetworkPacket(name,kind)
{
}

NotifyBoostrapList::NotifyBoostrapList(const NotifyBoostrapList& other) : ::BaseNetworkPacket(other)
{
    copy(other);
}

NotifyBoostrapList::~NotifyBoostrapList()
{
}

NotifyBoostrapList& NotifyBoostrapList::operator=(const NotifyBoostrapList& other)
{
    if (this==&other) return *this;
    ::BaseNetworkPacket::operator=(other);
    copy(other);
    return *this;
}

void NotifyBoostrapList::copy(const NotifyBoostrapList& other)
{
    this->Overlaykey = other.Overlaykey;
}

void NotifyBoostrapList::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaseNetworkPacket::parsimPack(b);
    doParsimPacking(b,this->Overlaykey);
}

void NotifyBoostrapList::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaseNetworkPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->Overlaykey);
}

const char * NotifyBoostrapList::getOverlaykey() const
{
    return this->Overlaykey.c_str();
}

void NotifyBoostrapList::setOverlaykey(const char * Overlaykey)
{
    this->Overlaykey = Overlaykey;
}

class NotifyBoostrapListDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    NotifyBoostrapListDescriptor();
    virtual ~NotifyBoostrapListDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(NotifyBoostrapListDescriptor)

NotifyBoostrapListDescriptor::NotifyBoostrapListDescriptor() : omnetpp::cClassDescriptor("NotifyBoostrapList", "BaseNetworkPacket")
{
    propertynames = nullptr;
}

NotifyBoostrapListDescriptor::~NotifyBoostrapListDescriptor()
{
    delete[] propertynames;
}

bool NotifyBoostrapListDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NotifyBoostrapList *>(obj)!=nullptr;
}

const char **NotifyBoostrapListDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NotifyBoostrapListDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NotifyBoostrapListDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int NotifyBoostrapListDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *NotifyBoostrapListDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "Overlaykey",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int NotifyBoostrapListDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='O' && strcmp(fieldName, "Overlaykey")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NotifyBoostrapListDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **NotifyBoostrapListDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *NotifyBoostrapListDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int NotifyBoostrapListDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NotifyBoostrapList *pp = (NotifyBoostrapList *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NotifyBoostrapListDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NotifyBoostrapList *pp = (NotifyBoostrapList *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NotifyBoostrapListDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NotifyBoostrapList *pp = (NotifyBoostrapList *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getOverlaykey());
        default: return "";
    }
}

bool NotifyBoostrapListDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NotifyBoostrapList *pp = (NotifyBoostrapList *)object; (void)pp;
    switch (field) {
        case 0: pp->setOverlaykey((value)); return true;
        default: return false;
    }
}

const char *NotifyBoostrapListDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *NotifyBoostrapListDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NotifyBoostrapList *pp = (NotifyBoostrapList *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


