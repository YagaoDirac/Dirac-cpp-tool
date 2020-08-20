#pragma once

#include<vector>
#include<string>
#include<iostream>

#include"include\DCT object.h"

class node_a :public DCT_node
{
public:
	node_a() {};
	virtual ~node_a()override {};
	static const char* type() { return "node_a"; };

	virtual void tick(float delta_time)override { if (delta_time < 2)return; std::cout << "node a tick()" << std::endl; };

	int node_aaaaaaa;
};
class node_b :public DCT_node
{
public:
	node_b() {};
	virtual ~node_b()override {};
	static const char* type() { return "node_b"; };

	virtual void tick(float delta_time)override { if (delta_time < 2)return; std::cout << "node b tick()" << std::endl; };

	int node_bbbbbb;
};


class comp_a :public DCT_component
{
public:
	comp_a() {};
	virtual ~comp_a()override {};
	static const char* type() { return "comp_a"; };

	virtual void tick(float delta_time)override { if (delta_time < 2)return; std::cout << "component a tick()" << std::endl; };

	int component_aaaaaa;
};


class comp_b :public DCT_component
{
public:
	comp_b() {};
	virtual ~comp_b()override {};
	static const char* type() { return "comp_b"; };

	virtual void tick(float delta_time)override { if (delta_time < 2)return; std::cout << "component b tick()" << std::endl; };

	int component_bbbbbb;
};



int main(int argc, char *argv[])
{
	DCT_memory_managing_backend* backend = new DCT_memory_managing_backend();

	//Finding child with type. This is not recursive.
	if(0)
	{
		node_a* root = new node_a();
		backend->add_root_node(root);

		root->create<node_a>();
		root->create<node_b>();
		root->create<comp_a>();
		root->create<comp_b>();

		root->find<node_b>()->tick(3);
		root->find<comp_a>()->tick(3);
	}


	//Memory leaking test.
	if (0)
	{
		//No leaking~
		for (int i = 0; i < 10000000; i++)
		{
			if (i % 10000 == 0)std::cout << i << std::endl;


			node_a* root = new node_a();//The first way of create DCT_object, directly new()

			root->create<node_a>();//The second way of create DCT_object, DCT_node::create()
			node_b* pos_b = new node_b();
			pos_b->set_parent(root);
			root->create<comp_a>();
			root->create<comp_b>();

			//root->receive_tick(1);
			//std::cout << std::endl;
	
			root->children[1]->remove();
			root->children[3]->remove();

			//root->receive_tick(0.1f);
			//std::cout << std::endl;

			root->try_clean();
			root->receive_tick(1);


			backend->add_root_node(root);
			root->remove();
			backend->try_clean_object();

			if (backend->root_nodes.size() != 0)std::cout << "wrong !!!!" << std::endl;
		}
	}

	//deleting a specific node automatically release its children's memory.
	if (1)
	{
		//No leaking~
		for (int i = 0; i < 1/*0000000*/; i++)
		{
			if (i % 10000 == 0)std::cout << i << std::endl;

			DCT_node* node = new node_a();
			backend->add_root_node(node);
			node->create<node_b>();
			node->create<node_a>();
			
			node = reinterpret_cast<DCT_node*>( node->children[1]);
			node->create<node_b>();
			node->create<node_a>();
			node->create<comp_b>();
			node->create<comp_a>();

			int breakpoint_here = 233;

			DCT_node* temp = reinterpret_cast<DCT_node*>(backend->root_nodes[0]->children[1]);
			temp->remove();
			//->children[1]->remove();

			breakpoint_here = 233;

			//2 ways to really release memory.
			backend->try_clean_object();
			//backend->try_clean_object();

			breakpoint_here = 233;

			backend->root_nodes[0]->remove();
			backend->try_clean_object();
		}
	}

	return 0;
}

