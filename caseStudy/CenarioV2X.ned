
import org.car2x.veins.nodes.RSU;
import org.car2x.veins.nodes.Scenario;

network CenarioV2X extends Scenario
{
	parameters:
        int numberOfRSUs = default(0); //whether to print debug output
    submodules:
        rsu[numberOfRSUs]: RSU {
            @display("p=150,140;b=10,10,oval");
        }
}

