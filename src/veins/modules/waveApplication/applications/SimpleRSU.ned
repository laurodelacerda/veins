
package org.car2x.veins.modules.waveApplication.applications;
import org.car2x.veins.modules.waveApplication.waveDevice.rsu.RSUDevice;

simple SimpleRSU extends RSUDevice
{
//    @class(RSUDevice);
    @display("i=block/app2");

	headerLength = 256bit;
	sendBeacons = false;
	
	maxOffset = 0.005s;
	
	sendData = true;
	dataOnSch = false;
	dataPriority = 3;
    
    applications = "emergency"; //application name
    applCommunication = "replicator"; //values: sender, receiver, replicator
}
