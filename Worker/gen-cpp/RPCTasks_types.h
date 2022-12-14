/**
 * Autogenerated by Thrift Compiler (0.17.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef RPCTasks_TYPES_H
#define RPCTasks_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <functional>
#include <memory>




struct Operation {
  enum type {
    ADD = 1,
    SUBTRACT = 2
  };
};

extern const std::map<int, const char*> _Operation_VALUES_TO_NAMES;

std::ostream& operator<<(std::ostream& out, const Operation::type& val);

std::string to_string(const Operation::type& val);

class Matrix;

typedef struct _Matrix__isset {
  _Matrix__isset() : id(false), resultMatrix(false), matrixA(false), matrixB(false), matrixResult(false) {}
  bool id :1;
  bool resultMatrix :1;
  bool matrixA :1;
  bool matrixB :1;
  bool matrixResult :1;
} _Matrix__isset;

class Matrix : public virtual ::apache::thrift::TBase {
 public:

  Matrix(const Matrix&);
  Matrix& operator=(const Matrix&);
  Matrix() noexcept
         : id(0),
           resultMatrix(0) {
  }

  virtual ~Matrix() noexcept;
  int32_t id;
  int32_t resultMatrix;
  std::vector<std::vector<int32_t> >  matrixA;
  std::vector<std::vector<int32_t> >  matrixB;
  std::vector<std::vector<int32_t> >  matrixResult;

  _Matrix__isset __isset;

  void __set_id(const int32_t val);

  void __set_resultMatrix(const int32_t val);

  void __set_matrixA(const std::vector<std::vector<int32_t> > & val);

  void __set_matrixB(const std::vector<std::vector<int32_t> > & val);

  void __set_matrixResult(const std::vector<std::vector<int32_t> > & val);

  bool operator == (const Matrix & rhs) const
  {
    if (!(id == rhs.id))
      return false;
    if (!(resultMatrix == rhs.resultMatrix))
      return false;
    if (!(matrixA == rhs.matrixA))
      return false;
    if (!(matrixB == rhs.matrixB))
      return false;
    if (!(matrixResult == rhs.matrixResult))
      return false;
    return true;
  }
  bool operator != (const Matrix &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Matrix & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot) override;
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const override;

  virtual void printTo(std::ostream& out) const;
};

void swap(Matrix &a, Matrix &b);

std::ostream& operator<<(std::ostream& out, const Matrix& obj);



#endif
