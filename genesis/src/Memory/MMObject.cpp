#include "MMObject.h"

std::unordered_map<std::type_index, long> MMObject::createCount;
std::unordered_map<std::type_index, std::stack<void*>> MMObject::deadObjects;
MMObject::Recycle MMObject::recycler;