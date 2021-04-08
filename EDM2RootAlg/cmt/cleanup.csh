# echo "cleanup EDM2RootAlg v0 in /afs/ihep.ac.cn/users/h/huyuxiang/junofs/trunk/offline/Examples"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v2r0-branch/ExternalLibs/CMT/v1r26
endif
source ${CMTROOT}/mgr/setup.csh
set cmtEDM2RootAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtEDM2RootAlgtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt cleanup -csh -pack=EDM2RootAlg -version=v0 -path=/afs/ihep.ac.cn/users/h/huyuxiang/junofs/trunk/offline/Examples  $* >${cmtEDM2RootAlgtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt cleanup -csh -pack=EDM2RootAlg -version=v0 -path=/afs/ihep.ac.cn/users/h/huyuxiang/junofs/trunk/offline/Examples  $* >${cmtEDM2RootAlgtempfile}"
  set cmtcleanupstatus=2
  /bin/rm -f ${cmtEDM2RootAlgtempfile}
  unset cmtEDM2RootAlgtempfile
  exit $cmtcleanupstatus
endif
set cmtcleanupstatus=0
source ${cmtEDM2RootAlgtempfile}
if ( $status != 0 ) then
  set cmtcleanupstatus=2
endif
/bin/rm -f ${cmtEDM2RootAlgtempfile}
unset cmtEDM2RootAlgtempfile
exit $cmtcleanupstatus

