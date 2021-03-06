/**
 * Copyright (C) 2013 Regents of the University of California.
 * See COPYING for copyright and distribution information.
 */
#ifndef WriteEcho_H
#define WriteEcho_H

#include "ndn-handle-common.hpp"
#include <queue>
class WriteEcho{
public:
  WriteEcho(Face* face, StorageHandle* p_handle, RepoCommandValidator validator);
  
  // onInterest for insert.
  void 
  onInterest(const Name& prefix, const Interest& interest);
  
  // onRegisterFailed for insert.
  void 
  onRegisterFailed(const Name& prefix, const std::string& reason);


  // onInterest for insert check.
  void 
  onCheckInterest(const Name& prefix, const Interest& interest);
  
  // onRegisterFailed for insert.
  void 
  onCheckRegisterFailed(const Name& prefix, const std::string& reason);

  void 
  validated(const shared_ptr<const Interest>& interest);

  void 
  validationFailed(const shared_ptr<const Interest>& interest);
  // Ask for Data insertation and when data comes
  void 
  onData(ndn::Face &face, const Interest& interest, Data& data, uint64_t processId);
  // Ask for Segmented Data insertation and when data comes
  // pipeNum is the pipeline number
  // segSent is the segment number of interest has been sent
  void 
  onSegData(ndn::Face &face, const Interest& interest, Data& data, uint64_t processId);
  // Ask for Data insertation and when data timeout
  void 
  onTimeout(ndn::Face &face, const Interest& interest);
  // Timeout when segment fetching, try three times
  void 
  onSegTimeout(ndn::Face &face, const Interest& interest, uint64_t processId);
  // Ask for Data when EndBlockId is null

  void 
  writeListen(const Name& prefix);

  void 
  writeCheckListen(const Name& prefix);


  //These three functions is for segmentation control
  //This function is to initiate fetching segmented data
  void 
  segInit(uint64_t processId, RepoCommandParameter rpara);
  //This function is control for send interests when onSegData
  void 
  segOnDataControl(uint64_t processId, const Interest& interest);
  //This function is control for sending interest when onSegTimeout
  void 
  segOnTimeoutControl(uint64_t processId, const Interest& interest);

  map<uint64_t, RepoCommandResponse> processMap;
private:
  Face* face_;
  RepoCommandValidator validator_;
  KeyChain keyChain_;
  int validres_;
  StorageHandle* p_handle_;
  //These 4 data structure is for credit based flow control, the index of map is processId
  map<uint64_t, queue<uint64_t> > nextSegQueueMap_;
  map<uint64_t, uint64_t> nextSegMap_;
  map<uint64_t, map<uint64_t, int> > retryMap_;
  map<uint64_t, int> creditMap_;
  map<uint64_t, boost::posix_time::ptime> noendTimeoutMap_;

  int retrytime_;
  int credit_;
  boost::posix_time::time_duration noendTimeout_;
};

#endif