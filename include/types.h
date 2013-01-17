
#include <stdint.h>

typedef uint32_t 	type_t
typedef uint16_t	value_t

typedef struct uuid_t {
	uint32_t	chunks[5];
} __attribute__ ((packed)) uuid_t;

typedef struct object_t {
	uuid_t		uuid;
	type_t		type;
	char		name[64];
	char		desc[256];
} __attribute__ ((packed)) object_t;

typedef struct attributes_t {
	value_t		hp;		// entities and items
	value_t		defense;	// items
	value_t		offense;	// items
	value_t		weight;		// items
	value_t		strength;	// entities
	value_t		endurance;	// entities
	value_t		perception;	// entities
	value_t		intelligence;	// entities
	value_t		wisdom;		// unused
	value_t		willpower;	// unused
	value_t		speed;		// unused
	value_t		luck;		// unused
} __attribute__ ((packed)) attributes_t;

typedef struct skills_t {
	value_t		melee;
	value_t		ranged;
	value_t		movement;
	value_t		potions;
} __attribute__ ((packed)) skills_t;

typedef struct inventory_t {
	uuid_t		primary_weapon;
	uuid_t		reserve_weapon;
	uuid_t		chest_armor;
	uuid_t		accessory_armor;
	uuid_t		carry[4];
	uuid_t		discard[4];
} __attribute__ ((packed)) inventory_t;

typedef struct item_t {
	object_t	header;
	attributes_t	attributes;
} __attribute__ ((packed)) inventory_t;

typedef struct entity_t {
	object_t	header;
	attributes_t	attributes;
	skills_t	skills;
	inventory_t	inventory;
	uuid_t		location;
} __attribute__ ((packed)) entity_t;
