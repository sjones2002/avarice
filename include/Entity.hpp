
#include "types.h"

namespace avarice {

	class Entity {
		private:
		entity_t	data;
		
		Item*		primary_weapon;
		Item*		reserve_weapon;
		Item*		chest_armor;
		Item*		accessory_armor;
		Item*		carry[4];
		Item*		discard[4];
		
		Location*	location;

		public:
			Entity		(entity_t* import);
			~Entity		(void);
		bool	fwrite		(int fd);
	
		Entity*	clone		(void);
	};

}
