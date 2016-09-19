
package org.car2x.veins.modules.waveApplication.waveDevice.obu;
import org.car2x.veins.modules.waveApplication.waveDevice.obu.BaseOBUDevice;

simple VehicleDevice extends BaseOBUDevice
{
    @class(VehicleDevice);
    @display("i=block/app2");
    string applications = default("emergency"); //application name
    string applCommunication = default("receiver"); //values: sender, receiver, fullduplex
    int roads = default(3);
}
