
#include "types.h"

namespace avarice {

	class Object {
	private:
		object_t 	data;
	
	public:

				Object		(object_t* import);
				~Object		(void);
			
		bool		fwrite		(int fd);
	
		Object*		clone		(void);
	};
	
}
