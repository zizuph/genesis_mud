
#ifndef _SPELL_LIST_SW_
#define _SPELL_LIST_SW_ 

#define N_SPELLS 20

#define ALL_SPELLS                                                \
                 ({ "physic", "smother", "sting", "lumin", \
                 	"vigilant", "herald", \
                    "darken", "cicerone", "veil", "cosmos",   \
                    "epee", "aegis", "temblor", "refuge", "phobia",     \
                    "thrall", "revenant", "espy", "espirit" })

#define SPELL_DESCRIPT({"heal yourself or others with dark power",\
	"extinguish flaming light sources","sting an enemy",\
	"light up the area", "cast a spell of protection", \
	"send a messenger to those you know","make the room dark", \
	"feel in the darkness",\
	"make yourself invisible","send a message to anyone",\
	"conjure a weapon for yourself","conjure armour for yourself",\
	"cause an earthquake","call a spirit to take you home",\
	"cause an enemy to flee","summon a spirit to fight for you",\
	"steal the life of an enemy","locate someone",\
	"possess someone"})

#define MANA_COST ({ 30, 15, 20, 15, 25, 20, 15, 20, 40, 35, 60, 70 \
					, 100, 120, 100, 150, 250, 200, 400 })

#define DEMON_DESCRIPT ({ "tiny", "small", "angry", "large", "powerful", \
	"montrous", "terrible", "many-fanged", "flame-spurting", "black" });
#endif
