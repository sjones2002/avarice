
#include "types.h"

namespace avarice {

	class Item {
		private:
		item_t		data;

		public:
			Item		(item_t* import);
			~Item		(void);

		bool	fwrite		(int fd);
	
		Item*	clone		(void);
	};

}
