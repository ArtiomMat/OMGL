#pragma once

namespace OMGL
{
  struct Exception
  {
    const char* str;
    Exception(const char* _str) : str(_str) {}
  };

  // General networking exception
  struct NetworkException : Exception
  {
    NetworkException(const char* _str) : Exception(_str) {}
  };

  // Exception with allocation or deletion.
  struct MemoryException : Exception
  {
    MemoryException(const char* _str) : Exception(_str) {}
  };
  // Exception when indexing memory, caught before a potential segfault.
  struct IndexException : MemoryException
  {
    IndexException(const char* _str) : MemoryException(_str) {}
  };

  // General file exception.
  struct FileException : Exception
  {
    FileException(const char* _str) : Exception(_str) {}
  };
  // Exception with opening a file.
  struct OpenException : FileException
  {
    OpenException(const char* _str) : FileException(_str) {}
  };
  // Exception with opening a file.
  struct ReadException : FileException
  {
    ReadException(const char* _str) : FileException(_str) {}
  };
  // Exception with opening a file.
  struct WriteException : FileException
  {
    WriteException(const char* _str) : FileException(_str) {}
  };

  // A system exception that has an unspecified reason, but from the libraries used.
  struct SystemException : Exception
  {
    SystemException(const char* _str) : Exception(_str) {}
  };
}