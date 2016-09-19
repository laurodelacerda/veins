
package org.car2x.veins.modules.waveApplication.applications;
import org.car2x.veins.modules.waveApplication.waveDevice.obu.VehicleDevice;

simple EmergencyOBU extends VehicleDevice
{
//    @class(OBUDevice);
    @display("i=block/app2");

	headerLength = 256bit;
	sendBeacons = false;
	
	maxOffset = 0.005s;
	
	sendData = true;
	dataOnSch = false;
	dataPriority = 1;
    
    //scheduleMsg = true;
    applications = "emergency"; //application name
    applCommunication = "creator"; //values: sender, receiver, replicator
}
