#include <string>
#include "/Users/tarannumislam/NFD1/daemon/fw/rebroadcast.hpp"
#include <iostream>
#include <functional>
#include "table/pit.hpp"
#include "table/pit-entry.hpp"
#include "algorithm.hpp"
#include <ndn-cxx/lp/tags.hpp>
#include "fw/strategy.hpp"
#include "ns3/node-container.h"
#include "ns3/node.h"
#include "face.hpp"
#include "tlv.hpp"
#include "ns3/node-list.h"
#include "ns3/random-variable-stream.h"
#include <ndn-cxx/lp/packet.hpp>
#include <vector>
#include <cmath>
#include "ns3/mobility-model.h"
#include <ndn-cxx/lp/packet.hpp>
#include "waypoint.h"
#include "ns3/vector.h"
#include "rebroadcast.hpp"
#include "forwarder.hpp"
using  namespace std ;
namespace nfd {
namespace fw {
    NFD_REGISTER_STRATEGY(REBROADCASTING);
    NFD_LOG_INIT(REBROADCASTING);
REBROADCASTING::REBROADCASTING(Forwarder& forwarder, const Name& name,const std::string& localUri,
  ,const std::string& remoteUri)
: Strategy(forwarder)
, ProcessNackTraits(this)
{
  m_faceTable.afterAdd.connect([this] (Face& face) {
    face.afterReceiveInterest.connect(
      [this, &face] (const Interest& interest, const EndpointId& endpointId) {
        this->startProcessInterest(FaceEndpoint(face, endpointId), interest);
      });
  }

  this->setInstanceName(makeInstanceName(name, getStrategyName()))
}

const Name&
REBROADCASTING::getStrategyName()
{
  static Name strategyName("/localhost/nfd/strategy/rebroadcast/%FD%00");
  return strategyName;
}
void 
REBROADCASTING::cancelrebroadcast()
{
  end m_schedule;
}
void 

REBROADCASTING::cancelrebroadcast()

{
m_schedule.end();
}

void
REBROADCASTING::afterReceiveInterest(const FaceEndpoint& ingress, const Interest& interest,
                                        const shared_ptr<pit::Entry>& pitEntry)
{
   const fib::NextHopList& nexthops = fibEntry->getNextHops();
   Time waitingTime;
     for (fib::NextHopList::const_iterator it = nexthops.begin(); it != nexthops.end(); ++it) {
        shared_ptr<Face> outFace = it->getFace();
        for 
        if (pitEntry->canForwardTo(*outFace)) {
          //add calculate wait timer schedule
            m_schedule = simulator::schedule(waitingtimer,Strategy::sendinterest((pitEntry, *outface, interest);),this); 
           //outFace = proposed outgoing face of the Interest
            NFD_LOG_DEBUG(interest << " from=" << ingress << " pitEntry-to=" << outFace.getId());
    
          if (!pitEntry->hasUnexpiredOutRecords()) 
        {
        this-> cancelrebroadcast();
        
        }

    }
     } // Action 1 to send new interest    
}                               

void
REBROADCASTING::computeWaitingTime(lp::GeoTag previousHop, Ptr<ns3::Packet> Packet)
{
    double maxRandomTimer = 0.002; // HARD CORDED FOR NOW
            UniformRandomVariable randomVariable;
            Time randomTimer = Seconds(randomVariable.GetValue(0, maxRandomTimer));
      // compute waiting time according to its own position and last hop's position

            // last hop position
            Vector3D lastHopPosition = Vector3D(previousHop.getPosX(), previousHop.getPosY(), 0);

            // own position
            Ptr<MobilityModel> mobility = m_node->GetObject<MobilityModel> ();
            if (mobility == 0) {
                    NS_FATAL_ERROR("Mobility model has to be installed on the node");
                    return randomTimer;
            }
            Vector3D currentPosition = mobility->GetPosition();

            // calculate distance
            double distToLastHop = CalculateDistance(lastHopPosition, currentPosition);
            if (distToLastHop < 0) {
                    NS_FATAL_ERROR("Mobility model is not valid");
                    return randomTimer;
            }

            Time waitingTimer;
            double minDelay = 0.005, maxDist = 150; 

            if (distToLastHop < maxDist) {
                    waitingTimer = Seconds(((maxDist - distToLastHop) / maxDist) * minDelay + randomTimer );
            }
            else {
                    NS_LOG_INFO("Tranmission distance is longer than max distance");
                    return randomTimer;
            }

            return waitingTimer;
}
} // namespace fw
} // namespace nfd
