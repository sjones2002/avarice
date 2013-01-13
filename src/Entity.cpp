

typedef struct entity_t {
	uuid_t	uuid;
	type_t	type;
	char	name[64];
	char	desc[256];
	value_t	hp;
	value_t	armor;
	value_t	strength;
	value_t	endurance;
	value_t	perception;
	value_t	intelligence;
	value_t	wisdom;
	value_t	willpower;
	value_t	luck;
} __attribute__ ((packed)) entity_t;




