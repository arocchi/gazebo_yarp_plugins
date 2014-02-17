/*
 * Copyright (C) 2007-2013 Istituto Italiano di Tecnologia RBCS & ADVR & iCub Facility
 * Authors: Francesco Romano, Silvio Traversaro, Enrico Mingo, Alessio Rocchi, Mirko Ferrati and Alessandro Settimi
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */


#ifndef GAZEBOYARP_PIDJOINTCONTROL_H
#define GAZEBOYARP_PIDJOINTCONTROL_H

class PIDJointControl {
    double _pGain;
    double _iGain;
    double _dGain;
    
public:
    PIDJointControl();
    ~PIDJointControl();
    
    double computeTorque();
    
    //Getter and setters
    double pGain();
    double iGain();
    double dGain();
    
    void setPGain(double pGain);
    void setIGain(double iGain);
    void setDGain(double dGain);
    
};


#endif
