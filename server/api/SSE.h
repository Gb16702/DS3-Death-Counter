#pragma once

#include "httplib.h"
#include "../memory/DS3StatsReader.h"

void streamStats(DS3StatsReader& statsReader, httplib::DataSink& sink);
