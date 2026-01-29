#include "files.h"
#include "/d/Immortal/rogon/open/spell/spell.h"
#include "/d/Immortal/rogon/open/spell/effect.h"
#include "damtypes.h"

#define FORM_ABJURATION     SS_FORM_ABJURATION
#define FORM_CONJURATION    SS_FORM_CONJURATION
#define FORM_DIVINATION     SS_FORM_DIVINATION
#define FORM_ENCHANTMENT    SS_FORM_ENCHANTMENT
#define FORM_ILLUSION	    SS_FORM_ILLUSION
#define FORM_TRANSMUTATION  SS_FORM_TRANSMUTATION

#define FORM_NAMES ([ \
    FORM_ABJURATION:	"abjuration",\
    FORM_CONJURATION:	"conjuration",\
    FORM_DIVINATION:	"divination",\
    FORM_ENCHANTMENT:	"enchantment",\
    FORM_ILLUSION:	"illusion",\
    FORM_TRANSMUTATION: "transmutation",\
])

#define ELEMENT_FIRE	SS_ELEMENT_FIRE
#define ELEMENT_WATER	SS_ELEMENT_WATER
#define ELEMENT_EARTH	SS_ELEMENT_EARTH
#define ELEMENT_AIR	SS_ELEMENT_AIR
#define ELEMENT_LIFE	SS_ELEMENT_LIFE
#define ELEMENT_DEATH	SS_ELEMENT_DEATH

#define ELEMENT_NAMES ([ \
    ELEMENT_FIRE:	"fire",\
    ELEMENT_WATER:	"water",\
    ELEMENT_EARTH:	"earth",\
    ELEMENT_AIR:	"air",\
    ELEMENT_LIFE:	"life",\
    ELEMENT_DEATH:	"death",\
])
/*--------------- New just for me. -------------------------*/

#define SPELL_I_DAM_TYPE       "_spell_i_dam_type"
#define SPELL_I_REVERSE_DEFENCE "_spell_i_reverse_defence"
#define SPELL_I_DAMAGE	       "_spell_i_damage"

#define SPELL_S_PARSE_FUN      "_spell_s_parse_fun"   /* Not used? */
#define SPELL_M_PARSE_OBJ      "_spell_o_parse_obj"
#define SPELL_S_CAST_FUN       "_spell_s_cast_fun"
#define SPELL_M_CAST_OBJ       "_spell_o_cast_obj"

#define SPELL_I_CLASS	       "_spell_i_class"       /* Used indeed. */
#define SPELL_M_CLASSES        "_spell_m_classes"     /* Not to be used! */
#define SPELL_S_NAME	       "_spell_s_name"	      /* Used indeed. */

#define SPELL_S_SYNTAX	       "_spell_s_syntax"
#define SPELL_S_DESC	       "_spell_s_desc"

#define SPELL_M_DATA	       "_spell_m_data"

#define SPELL_S_ARGS	       "_spell_s_args"
#define SPELL_O_ENVIRONMENT    "_spell_o_environment"

#define SERR_SYNTAX	       -1

/*--------------- Some handy macros. -----------------------*/

#define set_elem(elem, needed) \
    add_prop(SPELL_I_ELEMENT_SKILL, elem); \
    add_prop(SPELL_I_ELEMENT_NEEDED, needed)

#define set_form(form, needed) \
    add_prop(SPELL_I_FORM_SKILL, form); \
    add_prop(SPELL_I_FORM_NEEDED, needed)

#define set_spell_name(name) \
    add_prop(SPELL_S_NAME, name)

#define set_classes(classes) \
    add_prop(SPELL_M_CLASSES, classes)

#define set_dt(dt) \
    add_prop(SPELL_I_DAM_TYPE, dt)

#define set_dam(dam) \
    add_prop(SPELL_I_DAMAGE, dam)

#define set_reverse() \
    add_prop(SPELL_I_REVERSE_DEFENCE, 1)

#define set_desc(desc) \
    add_prop(SPELL_S_DESC, desc)

#define set_syntax(syntax) \
    add_prop(SPELL_S_SYNTAX, syntax)
