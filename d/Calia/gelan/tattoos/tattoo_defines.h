#define TPQP this_player()->query_possessive()
#define SUBLOC "_tattoo_shadow_desc_"
#define TATTOO_MAX_NUMBER 4
#define TATTOO_OBJECT "/d/Calia/gelan/tattoos/tattoo"
#define TATTOO_SCAR "/d/Calia/gelan/tattoos/tattoo_scar"
#define TATTOO_SAVE_DIR "/d/Calia/gelan/tattoos/tattoo_save/"
#define TATTOO_RECOVER TATTOO_SAVE_DIR+\
    this_player()->query_real_name()[0..0]+"/"+\
    "tattoo_save_"+this_player()->query_real_name()+".o"
#define TATTOO_SAVE TATTOO_SAVE_DIR+\
    environment()->query_real_name()[0..0]+"/"+\
    "tattoo_save_"+environment()->query_real_name()
#define MASTER_TATTOO "/d/Calia/gelan/tattoos/master_tattoo"
#define TATTOO_ARTIST "/d/Calia/gelan/monsters/budda"
#define BASE "/d/Calia/gelan/tattoos/signs/"
