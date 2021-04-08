#include "EDM2RootAlg.h"
#include "SniperKernel/AlgFactory.h"
#include "DataRegistritionSvc/DataRegistritionSvc.h"
#include "BufferMemMgr/IDataMemMgr.h"
#include "EvtNavigator/NavBuffer.h"
#include "Event/PhyHeader.h"
#include "Event/PhyEvent.h"

#include "Event/SimHeader.h"
#include "Event/SimEvent.h"
#include "Event/SimPMTHit.h"


#ifdef WITH_G4OPTICKS
#error "OPTICKS is enabled. Maybe you are set the envvar CMTEXTRATAGS=opticks"
#endif

DECLARE_ALGORITHM(EDM2RootAlg);

EDM2RootAlg::EDM2RootAlg(const std::string& name)
    : AlgBase(name)
{
    declProp("output",outputfile = "user.root");
}

bool EDM2RootAlg::initialize()
{
    LogDebug << "initializing" << std::endl;

    SniperDataPtr<JM::NavBuffer>  navBuf(getParent(), "/Event");
    if ( navBuf.invalid() ) {
        LogError << "cannot get the NavBuffer @ /Event" << std::endl;
        return false;
    }
    m_buf = navBuf.data();
 

    TString of = outputfile;   
    f = new TFile(of, "RECREATE");
    h = new TTree("simevent","simevent");
    h->Branch("t_evtID", &t_evtID, "t_evtID/I");
    h->Branch("t_cdhits", &t_cdhits, "t_cdhits/I");  
    h->Branch("t_hittime", &t_hittime);
    h->Branch("t_pmtid", &t_pmtid);
 
    t_evtID=0;
    t_cdhits=0;
    t_hittime.clear();
    t_pmtid.clear();
  


    return true;
}

bool EDM2RootAlg::execute()
{
    JM::SimEvent* simevent = 0;
    JM::EvtNavigator* nav = m_buf->curEvt();
    JM::SimHeader* simheader = static_cast<JM::SimHeader*>(nav->getHeader("/Event/Sim"));
    if (simheader) {
        simevent  = (JM::SimEvent*)simheader->event();
        LogInfo << "SimEvent Read in: " << simevent << std::endl;
        LogInfo << "SimEvent Track: " << simevent->getTracksVec().size() << std::endl;
        LogInfo << "SimEvent CD Hits: " << simevent->getCDHitsVec().size() << std::endl;
        LogInfo << "SimEvent WP Hits: " << simevent->getWPHitsVec().size() << std::endl;
        LogInfo << "SimEvent TT Hits: " << simevent->getTTHitsVec().size() << std::endl;
        LogInfo << "SimEvent m_nhits: " << (simevent->getCDHitsVec().size()+simevent->getWPHitsVec().size()+simevent->getTTHitsVec().size())<< std::endl;
    }
     t_evtID = simevent->getEventID();
     t_cdhits= simevent->getCDHitsVec().size();
 //  std::vector<SimPMTHit*> cd_hit =0;
   std::vector<JM::SimPMTHit*> cd_hit = simevent->getCDHitsVec();
   for(auto jm_hit : cd_hit ) {
           t_pmtid.push_back(jm_hit->getPMTID());
           t_hittime.push_back(jm_hit->getHitTime()); 
          // std::cout<<jm_hit->getPMTID()<<std::endl;
     }
       
    

    h->Fill();
   
    t_evtID=0;
    t_cdhits=0;
    t_hittime.clear();
    t_pmtid.clear();
    
    return true;
}

bool EDM2RootAlg::finalize()
{
 //   h->Fill();
    f->cd();
    h->Write();
    f->Close();   
    LogDebug << "finalizing" << std::endl;
    return true;
}
