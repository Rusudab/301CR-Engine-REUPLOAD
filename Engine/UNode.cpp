#include "UNode.h"

UNode::UNode()
{

}

UNode::~UNode()
{

}

UNode::UNode(std::string mp, std::string tp)
{
	mpath = mp;
	tpath = tp;
}

void UNode::AttachNode(IAnimatedMeshSceneNode* nd)
{
	node = nd;
}
