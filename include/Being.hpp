
using namespace std;

class Being: public Entity {
private:
	entity_t 	attr;
	Item*		item_l;
	Effect*		effect_l;
	Location*	location;
	

public:
	bool		fwrite		(char* filename);
	bool		fread		(char* filename);
	
	void		apply_item	(Item* item);
	void		apply_effect	(Effect* effect);
	
	void		add_item	(Item* item);
	void		del_item	(item* item);
	
	Location*	move		(Location_t* goal);
	
};



