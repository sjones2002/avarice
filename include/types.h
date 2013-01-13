
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

typedef struct item_t {
	value_t		weight;
	byte		modifier_count;
} __attribute__ ((packed)) item_t;

typedef struct modifier_t {
	value_t		value;
	uuid_t		enable_trigger;
	uuid_t		activation_trigger;
} __attribute__ ((packed)) modifier_t;

typedef struct attributes_t {
	value_t		hp;
	value_t		armor;
	value_t		strength;
	value_t		endurance;
	value_t		perception;
	value_t		intelligence;
	value_t		wisdom;
	value_t		willpower;
	value_t		luck;
} __attribute__ ((packed)) attributes_t;
