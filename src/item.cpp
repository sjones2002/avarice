
using namespace std;

typedef struct uuid_t {
	uint32_t	chunks[5];
} __attribute__ ((packed)) uuid_t;

typedef uint32_t 	type_t
typedef uint16_t	value_t

typedef struct item_t {
	uuid_t	uuid;
	type_t	type;
	char	name[64];
	char	desc[256];
	value_t	weight;
	byte	modifier_count;
} __attribute__ ((packed)) item_t;

typedef struct modifier_t {
	uuid_t		uuid;
	type_t		type;
	char		name[64];
	char		desc[256];
	value_t		value;
	uuid_t		enable_trigger;
	uuid_t		activation_trigger;
} __attribute__ ((packed)) modifier_t;

class Item: public Object {
private:
	item_t 		attr;
	modifier_t* 	mods;
	Object*		owner;
	
	int	apply_modifiers	(attributes_t* attr);

public:
	int	fwrite		(char* filename);
	int	fread		(char* filename);
	
	bool	is_enabled	(void);
	int	influence	(void);
	int	activate	(Object* target);
	
	int	transfer	(Object* target);
	int	destroy		(void);
	int	clone		(Object* target);
	
	int	upgrade		(modifier_t* mods);
	int	supplant	(modifier_t* mods);
};
