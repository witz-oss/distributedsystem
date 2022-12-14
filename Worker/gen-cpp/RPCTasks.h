/**
 * Autogenerated by Thrift Compiler (0.17.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef RPCTasks_H
#define RPCTasks_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include <memory>
#include "RPCTasks_types.h"



#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class RPCTasksIf {
 public:
  virtual ~RPCTasksIf() {}
  virtual bool assignMatrix(const Matrix& matrix) = 0;
  virtual bool calcMatrix(const Operation::type op) = 0;
  virtual void saveMatrix() = 0;
  virtual void ping(const std::string& msg) = 0;
};

class RPCTasksIfFactory {
 public:
  typedef RPCTasksIf Handler;

  virtual ~RPCTasksIfFactory() {}

  virtual RPCTasksIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(RPCTasksIf* /* handler */) = 0;
  };

class RPCTasksIfSingletonFactory : virtual public RPCTasksIfFactory {
 public:
  RPCTasksIfSingletonFactory(const ::std::shared_ptr<RPCTasksIf>& iface) : iface_(iface) {}
  virtual ~RPCTasksIfSingletonFactory() {}

  virtual RPCTasksIf* getHandler(const ::apache::thrift::TConnectionInfo&) override {
    return iface_.get();
  }
  virtual void releaseHandler(RPCTasksIf* /* handler */) override {}

 protected:
  ::std::shared_ptr<RPCTasksIf> iface_;
};

class RPCTasksNull : virtual public RPCTasksIf {
 public:
  virtual ~RPCTasksNull() {}
  bool assignMatrix(const Matrix& /* matrix */) override {
    bool _return = false;
    return _return;
  }
  bool calcMatrix(const Operation::type /* op */) override {
    bool _return = false;
    return _return;
  }
  void saveMatrix() override {
    return;
  }
  void ping(const std::string& /* msg */) override {
    return;
  }
};

typedef struct _RPCTasks_assignMatrix_args__isset {
  _RPCTasks_assignMatrix_args__isset() : matrix(false) {}
  bool matrix :1;
} _RPCTasks_assignMatrix_args__isset;

class RPCTasks_assignMatrix_args {
 public:

  RPCTasks_assignMatrix_args(const RPCTasks_assignMatrix_args&);
  RPCTasks_assignMatrix_args& operator=(const RPCTasks_assignMatrix_args&);
  RPCTasks_assignMatrix_args() noexcept {
  }

  virtual ~RPCTasks_assignMatrix_args() noexcept;
  Matrix matrix;

  _RPCTasks_assignMatrix_args__isset __isset;

  void __set_matrix(const Matrix& val);

  bool operator == (const RPCTasks_assignMatrix_args & rhs) const
  {
    if (!(matrix == rhs.matrix))
      return false;
    return true;
  }
  bool operator != (const RPCTasks_assignMatrix_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const RPCTasks_assignMatrix_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class RPCTasks_assignMatrix_pargs {
 public:


  virtual ~RPCTasks_assignMatrix_pargs() noexcept;
  const Matrix* matrix;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _RPCTasks_assignMatrix_result__isset {
  _RPCTasks_assignMatrix_result__isset() : success(false) {}
  bool success :1;
} _RPCTasks_assignMatrix_result__isset;

class RPCTasks_assignMatrix_result {
 public:

  RPCTasks_assignMatrix_result(const RPCTasks_assignMatrix_result&) noexcept;
  RPCTasks_assignMatrix_result& operator=(const RPCTasks_assignMatrix_result&) noexcept;
  RPCTasks_assignMatrix_result() noexcept
                               : success(0) {
  }

  virtual ~RPCTasks_assignMatrix_result() noexcept;
  bool success;

  _RPCTasks_assignMatrix_result__isset __isset;

  void __set_success(const bool val);

  bool operator == (const RPCTasks_assignMatrix_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const RPCTasks_assignMatrix_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const RPCTasks_assignMatrix_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _RPCTasks_assignMatrix_presult__isset {
  _RPCTasks_assignMatrix_presult__isset() : success(false) {}
  bool success :1;
} _RPCTasks_assignMatrix_presult__isset;

class RPCTasks_assignMatrix_presult {
 public:


  virtual ~RPCTasks_assignMatrix_presult() noexcept;
  bool* success;

  _RPCTasks_assignMatrix_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _RPCTasks_calcMatrix_args__isset {
  _RPCTasks_calcMatrix_args__isset() : op(false) {}
  bool op :1;
} _RPCTasks_calcMatrix_args__isset;

class RPCTasks_calcMatrix_args {
 public:

  RPCTasks_calcMatrix_args(const RPCTasks_calcMatrix_args&) noexcept;
  RPCTasks_calcMatrix_args& operator=(const RPCTasks_calcMatrix_args&) noexcept;
  RPCTasks_calcMatrix_args() noexcept
                           : op(static_cast<Operation::type>(0)) {
  }

  virtual ~RPCTasks_calcMatrix_args() noexcept;
  /**
   * 
   * @see Operation
   */
  Operation::type op;

  _RPCTasks_calcMatrix_args__isset __isset;

  void __set_op(const Operation::type val);

  bool operator == (const RPCTasks_calcMatrix_args & rhs) const
  {
    if (!(op == rhs.op))
      return false;
    return true;
  }
  bool operator != (const RPCTasks_calcMatrix_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const RPCTasks_calcMatrix_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class RPCTasks_calcMatrix_pargs {
 public:


  virtual ~RPCTasks_calcMatrix_pargs() noexcept;
  /**
   * 
   * @see Operation
   */
  const Operation::type* op;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _RPCTasks_calcMatrix_result__isset {
  _RPCTasks_calcMatrix_result__isset() : success(false) {}
  bool success :1;
} _RPCTasks_calcMatrix_result__isset;

class RPCTasks_calcMatrix_result {
 public:

  RPCTasks_calcMatrix_result(const RPCTasks_calcMatrix_result&) noexcept;
  RPCTasks_calcMatrix_result& operator=(const RPCTasks_calcMatrix_result&) noexcept;
  RPCTasks_calcMatrix_result() noexcept
                             : success(0) {
  }

  virtual ~RPCTasks_calcMatrix_result() noexcept;
  bool success;

  _RPCTasks_calcMatrix_result__isset __isset;

  void __set_success(const bool val);

  bool operator == (const RPCTasks_calcMatrix_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const RPCTasks_calcMatrix_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const RPCTasks_calcMatrix_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _RPCTasks_calcMatrix_presult__isset {
  _RPCTasks_calcMatrix_presult__isset() : success(false) {}
  bool success :1;
} _RPCTasks_calcMatrix_presult__isset;

class RPCTasks_calcMatrix_presult {
 public:


  virtual ~RPCTasks_calcMatrix_presult() noexcept;
  bool* success;

  _RPCTasks_calcMatrix_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class RPCTasks_saveMatrix_args {
 public:

  RPCTasks_saveMatrix_args(const RPCTasks_saveMatrix_args&) noexcept;
  RPCTasks_saveMatrix_args& operator=(const RPCTasks_saveMatrix_args&) noexcept;
  RPCTasks_saveMatrix_args() noexcept {
  }

  virtual ~RPCTasks_saveMatrix_args() noexcept;

  bool operator == (const RPCTasks_saveMatrix_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const RPCTasks_saveMatrix_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const RPCTasks_saveMatrix_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class RPCTasks_saveMatrix_pargs {
 public:


  virtual ~RPCTasks_saveMatrix_pargs() noexcept;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class RPCTasks_saveMatrix_result {
 public:

  RPCTasks_saveMatrix_result(const RPCTasks_saveMatrix_result&) noexcept;
  RPCTasks_saveMatrix_result& operator=(const RPCTasks_saveMatrix_result&) noexcept;
  RPCTasks_saveMatrix_result() noexcept {
  }

  virtual ~RPCTasks_saveMatrix_result() noexcept;

  bool operator == (const RPCTasks_saveMatrix_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const RPCTasks_saveMatrix_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const RPCTasks_saveMatrix_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class RPCTasks_saveMatrix_presult {
 public:


  virtual ~RPCTasks_saveMatrix_presult() noexcept;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _RPCTasks_ping_args__isset {
  _RPCTasks_ping_args__isset() : msg(false) {}
  bool msg :1;
} _RPCTasks_ping_args__isset;

class RPCTasks_ping_args {
 public:

  RPCTasks_ping_args(const RPCTasks_ping_args&);
  RPCTasks_ping_args& operator=(const RPCTasks_ping_args&);
  RPCTasks_ping_args() noexcept
                     : msg() {
  }

  virtual ~RPCTasks_ping_args() noexcept;
  std::string msg;

  _RPCTasks_ping_args__isset __isset;

  void __set_msg(const std::string& val);

  bool operator == (const RPCTasks_ping_args & rhs) const
  {
    if (!(msg == rhs.msg))
      return false;
    return true;
  }
  bool operator != (const RPCTasks_ping_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const RPCTasks_ping_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class RPCTasks_ping_pargs {
 public:


  virtual ~RPCTasks_ping_pargs() noexcept;
  const std::string* msg;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class RPCTasks_ping_result {
 public:

  RPCTasks_ping_result(const RPCTasks_ping_result&) noexcept;
  RPCTasks_ping_result& operator=(const RPCTasks_ping_result&) noexcept;
  RPCTasks_ping_result() noexcept {
  }

  virtual ~RPCTasks_ping_result() noexcept;

  bool operator == (const RPCTasks_ping_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const RPCTasks_ping_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const RPCTasks_ping_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class RPCTasks_ping_presult {
 public:


  virtual ~RPCTasks_ping_presult() noexcept;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class RPCTasksClient : virtual public RPCTasksIf {
 public:
  RPCTasksClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  RPCTasksClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  bool assignMatrix(const Matrix& matrix) override;
  void send_assignMatrix(const Matrix& matrix);
  bool recv_assignMatrix();
  bool calcMatrix(const Operation::type op) override;
  void send_calcMatrix(const Operation::type op);
  bool recv_calcMatrix();
  void saveMatrix() override;
  void send_saveMatrix();
  void recv_saveMatrix();
  void ping(const std::string& msg) override;
  void send_ping(const std::string& msg);
  void recv_ping();
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class RPCTasksProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::std::shared_ptr<RPCTasksIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext) override;
 private:
  typedef  void (RPCTasksProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_assignMatrix(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_calcMatrix(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_saveMatrix(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_ping(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  RPCTasksProcessor(::std::shared_ptr<RPCTasksIf> iface) :
    iface_(iface) {
    processMap_["assignMatrix"] = &RPCTasksProcessor::process_assignMatrix;
    processMap_["calcMatrix"] = &RPCTasksProcessor::process_calcMatrix;
    processMap_["saveMatrix"] = &RPCTasksProcessor::process_saveMatrix;
    processMap_["ping"] = &RPCTasksProcessor::process_ping;
  }

  virtual ~RPCTasksProcessor() {}
};

class RPCTasksProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  RPCTasksProcessorFactory(const ::std::shared_ptr< RPCTasksIfFactory >& handlerFactory) noexcept :
      handlerFactory_(handlerFactory) {}

  ::std::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo) override;

 protected:
  ::std::shared_ptr< RPCTasksIfFactory > handlerFactory_;
};

class RPCTasksMultiface : virtual public RPCTasksIf {
 public:
  RPCTasksMultiface(std::vector<std::shared_ptr<RPCTasksIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~RPCTasksMultiface() {}
 protected:
  std::vector<std::shared_ptr<RPCTasksIf> > ifaces_;
  RPCTasksMultiface() {}
  void add(::std::shared_ptr<RPCTasksIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  bool assignMatrix(const Matrix& matrix) override {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->assignMatrix(matrix);
    }
    return ifaces_[i]->assignMatrix(matrix);
  }

  bool calcMatrix(const Operation::type op) override {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->calcMatrix(op);
    }
    return ifaces_[i]->calcMatrix(op);
  }

  void saveMatrix() override {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->saveMatrix();
    }
    ifaces_[i]->saveMatrix();
  }

  void ping(const std::string& msg) override {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->ping(msg);
    }
    ifaces_[i]->ping(msg);
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class RPCTasksConcurrentClient : virtual public RPCTasksIf {
 public:
  RPCTasksConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot, std::shared_ptr< ::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(prot);
  }
  RPCTasksConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot, std::shared_ptr< ::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  bool assignMatrix(const Matrix& matrix) override;
  int32_t send_assignMatrix(const Matrix& matrix);
  bool recv_assignMatrix(const int32_t seqid);
  bool calcMatrix(const Operation::type op) override;
  int32_t send_calcMatrix(const Operation::type op);
  bool recv_calcMatrix(const int32_t seqid);
  void saveMatrix() override;
  int32_t send_saveMatrix();
  void recv_saveMatrix(const int32_t seqid);
  void ping(const std::string& msg) override;
  int32_t send_ping(const std::string& msg);
  void recv_ping(const int32_t seqid);
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  std::shared_ptr< ::apache::thrift::async::TConcurrentClientSyncInfo> sync_;
};

#ifdef _MSC_VER
  #pragma warning( pop )
#endif



#endif
