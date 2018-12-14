#pragma once

#define SafeDelete(x) if(x) {delete x; x = nullptr;}