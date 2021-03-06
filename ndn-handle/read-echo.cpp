/**
 * Copyright (C) 2013 Regents of the University of California.
 * See COPYING for copyright and distribution information.
 */
#include "read-echo.hpp"

// Interest.
void 
ReadEcho::onInterest(const Name& prefix, const Interest& interest) {
  std::cout << "<< I: " << interest.getName() << std::endl;

  Name name = Name(interest.getName());
  Data data = Data(interest.getName());

  p_handle_->check_data(interest, data);

  //keyChain_.sign(data);
  
  std::cout << ">> D: "<<"size: "<<data.wireEncode().size()<<endl;
  cout<<">> D: data: "<<data.wireEncode().wire()<<endl;
  face_->put(data);
}

// onRegisterFailed.
void 
ReadEcho::onRegisterFailed(const Name& prefix, const std::string& reason){
  std::cerr << "ERROR: Failed to register prefix in local hub's daemon" << std::endl;
  face_->shutdown();
}

void 
ReadEcho::readListen(const Name& prefix){
  (*face_).setInterestFilter(prefix,
                            func_lib::bind(&ReadEcho::onInterest, this, _1, _2),
                            func_lib::bind(&ReadEcho::onRegisterFailed, this, _1, _2));
}