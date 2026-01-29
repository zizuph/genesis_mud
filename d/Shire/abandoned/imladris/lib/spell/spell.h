#ifndef _SPELL_H_
#define _SPELL_H_ 1

#define SPELL_I_IS	       "_spell_i_is"		/* New. */
#define SPELL_I_GENERAL        "_spell_i_general"	/* New. */
#define SPELL_I_FORM_SKILL     "_spell_i_form_skill"
#define SPELL_I_FORM_NEEDED    "_spell_i_form_needed"
#define SPELL_I_ELEMENT_SKILL  "_spell_i_element_skill"
#define SPELL_I_ELEMENT_NEEDED "_spell_i_element_needed"
#define SPELL_AM_MATERIALS     "_spell_am_materials"
#define SPELL_I_CASTING_TIME   "_spell_i_casting_time"
#define SPELL_I_DIFFICULTY     "_spell_i_difficulty"
#define SPELL_I_MANA	       "_spell_i_mana"
#define SPELL_O_EFFECT	       "_spell_o_effect"
#define SPELL_I_ATTACK	       "_spell_i_attack"
#define SPELL_I_DURATION       "_spell_i_duration"
#define SPELL_I_EFFECT_TYPE    "_spell_i_effect_type"	/* New. */
#define SPELL_O_MAGICAL_ITEM   "_spell_o_magical_item"

#define DURATION_INSTANT	0
#define DURATION_UNTIL_REBOOT	-1
#define DURATION_PERMANENT	-2

/* This property is set so that counter-spells can destruct the
   spell which is about to take place (use dispel_effect). */

#define LIVE_O_CONSENTRATES_SPELL "_live_o_consentrates_spell"

#endif
