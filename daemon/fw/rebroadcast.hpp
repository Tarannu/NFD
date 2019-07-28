#ifndef REBROADCASTING_STRATEGY
#define REBROADCASTING_STRATEGY
#include <string>
#include "fw/strategy.hpp"
#include "forwarder.hpp"
#include "algorithm.hpp"
#include "table/measurements-accessor.hpp"
#include "strategy.hpp"
#include "table/fib.hpp"
#include "table/pit.hpp"
#include "table/cs.hpp"
#include "table/dead-nonce-list.hpp"
#include "ns3/ndnSIM/model/cs/ndn-content-store.hpp"
#include "table/name-tree-entry.hpp"
#include <ndn-cxx/lp/tags.hpp>
#include "ns-3/ndnSIM/ndn-cxx/lp/geo-tag.hpp"
namespace nfd {
namespace fw  {

             
  
 class REBROADCASTING : public Strategy
   {
    public:
      explicit
      REBROADCASTING(Forwarder& forwarder, const Name& name = getStrategyName());
       virtual ~REBROADCASTING() override;
      static const Name& getStrategyName();


  void
  afterReceiveInterest(const FaceEndpoint& ingress, const Interest& interest,
                       const shared_ptr<pit::Entry>& pitEntry) override;
   }

  void 
  REBROADCASTING::cancelrebroadcast(lp::GeoTag previousHop,lp::GeoTag previousTOpreviousHop, Ptr<ns3::Packet> Packet)
    public: // forwarding entrypoints and tables
  /** \brief start incoming Interest processing
   *  \param ingress face on which Interest is received and endpoint of the sender
   *  \param interest the incoming Interest, must be well-formed and created with make_shared
   */
  void
  startProcessInterest(const FaceEndpoint& ingress, const Interest& interest)
  {
    this->onIncomingInterest(ingress, interest);
  }
  EventId m_scheduledSend;
  Fib&
  getFib()
  {
    return m_fib;
  }

  Pit&
  getPit()
  {
    return m_pit;
    
  }
  Pit&
  getinterest()
  {
    return m_interest;
  }
  StrategyChoice&
  getStrategyChoice()
  {
    return m_strategyChoice;
  }

  PUBLIC_WITH_TESTS_ELSE_PRIVATE: // pipelines
VIRTUAL_WITH_TESTS void
  onInterestLoop(const FaceEndpoint& ingress, const Interest& interest);
  
 
private:
  
      virtual Time
      computeWaitingTime(lp::GeoTag previousHop, Ptr<ns3::Packet> Packet);
   //virtual void 
   //SendFromQueue();

      Ptr<NetDevice> m_netDevice; ///< \brief Smart pointer to NetDevice
      Ptr<Node> m_node;

      EventId m_scheduledSend;

      lp::GeoTag m_geoTag; // GeoTag object
    friend double CalculateDistance (const Vector3D &a, const Vector3D &b);
    friend double CalculateAngleandProjection (const Vector3D &a, const Vector3D &b);

 // std::set<std::tuple<lp::Packet, Name, uint64_t, int>, comp> m_queue
 // packet queue
      
  FaceTable m_faceTable;
 Ptr<ns3::Packet> packet;

  

  // allow Strategy (base class) to enter pipelines
  friend class fw::Strategy;
}; //namespace fw

} // namespace nfd

  #endif // NFD_DAEMON_FW_REBROADCAST_STRATEGY
