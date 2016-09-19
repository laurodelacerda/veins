
package org.car2x.veins.modules.waveApplication.waveDevice.rsu;
import org.car2x.veins.modules.waveApplication.BaseWaveApplicationLayer;

simple RSUDevice extends BaseWaveApplicationLayer
{
    @class(RSUDevice);
    @display("i=block/app2");
    string applications = default("emergency"); //application name
    string applCommunication = default("receiver"); //values: sender, receiver, fullduplex
    int roads = default(3);
}
