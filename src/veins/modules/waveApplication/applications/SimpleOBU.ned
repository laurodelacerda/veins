
package org.car2x.veins.modules.waveApplication.applications;
import org.car2x.veins.modules.waveApplication.waveDevice.obu.VehicleDevice;

simple SimpleOBU extends VehicleDevice
{
//    @class(OBUDevice);
    @display("i=block/app2");

	headerLength = 256bit;
	sendBeacons = false;
	
	maxOffset = 0.005s;
	
	sendData = true;
	dataOnSch = false;
	dataPriority = 3;
	
    applications = "emergency"; //application name
    //applCommunication = "replicator"; //values: sender, receiver, fullduplex
    roads = 0;
}
