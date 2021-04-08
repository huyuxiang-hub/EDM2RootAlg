#!/usr/bin/python

import argparse
parser = argparse.ArgumentParser(description='count to script')
parser.add_argument("--input",default="SimEvent.root")
parser.add_argument("--output",default="user.root")
args = parser.parse_args()


import Sniper
task = Sniper.TopTask("task")
task.setLogLevel(2)

import EDM2RootAlg
alg = task.createAlg("EDM2RootAlg/alg_example")
alg.property("output").set(args.output)
import BufferMemMgr
bufMgr = task.createSvc("BufferMemMgr")



import RootIOTools
riSvc = task.createSvc("MergingInputSvc/InputSvc")
riSvc.property("MergingEventType").set("SimEvent")
riSvc.property("MergingEventPath").set("/Event/Sim")
#riSvc.property("MergingEventPath").set("/Event/SimEvent")
riSvc.property("InputFile").set(args.input)

'''
import RootIOSvc
ro = task.createSvc("RootOutputSvc/OutputSvc")
output_streams = {}
output_streams["/Event/Sim"] ="SimEventMerge.root"
ro.property("OutputStreams").set(output_streams)
'''

task.setEvtMax(-1)
task.show()
task.run()
