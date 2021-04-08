# echo "setup EDM2RootAlg v0 in /afs/ihep.ac.cn/users/h/huyuxiang/junofs/trunk/offline/Examples"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J20v2r0-branch/ExternalLibs/CMT/v1r26; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtEDM2RootAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtEDM2RootAlgtempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=EDM2RootAlg -version=v0 -path=/afs/ihep.ac.cn/users/h/huyuxiang/junofs/trunk/offline/Examples  -no_cleanup $* >${cmtEDM2RootAlgtempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt setup -sh -pack=EDM2RootAlg -version=v0 -path=/afs/ihep.ac.cn/users/h/huyuxiang/junofs/trunk/offline/Examples  -no_cleanup $* >${cmtEDM2RootAlgtempfile}"
  cmtsetupstatus=2
  /bin/rm -f ${cmtEDM2RootAlgtempfile}
  unset cmtEDM2RootAlgtempfile
  return $cmtsetupstatus
fi
cmtsetupstatus=0
. ${cmtEDM2RootAlgtempfile}
if test $? != 0 ; then
  cmtsetupstatus=2
fi
/bin/rm -f ${cmtEDM2RootAlgtempfile}
unset cmtEDM2RootAlgtempfile
return $cmtsetupstatus

