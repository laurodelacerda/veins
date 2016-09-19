
package org.car2x.veins.modules.waveApplication.waveDevice.obu;
import org.car2x.veins.modules.waveApplication.BaseWaveApplicationLayer;

simple BaseOBUDevice extends BaseWaveApplicationLayer
{
    @class(BaseOBUDevice);
    @display("i=block/app2");
//    string applications = default("emergency"); //application name
//    string applCommunication = default("receiver"); //values: sender, receiver, fullduplex
}
