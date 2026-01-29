#include "/d/Krynn/gnome/local.h"

#define GUILDMASTERS    ({ capitalize(WIZARD_IN_CHARGE), "Aridor" })
#define GOBJ 		GGUILD + "obj/"
#define GNOME_SOUL 	GOBJ + "kgnome_soul"
#define GNOME_SHADOW    GOBJ + "race_shadow"
#define GNOME_NAME	"Gnomish Inventors"
#define GNOME_TAX       2
#define GNOME_OBJ       GOBJ + "gizmo.c"
#define GNOME_TITLES    ({"", "new Krynn Gnome", \
			    "Gnome Aide", \
			    "Gnome Mate", \
			    "Novice Tinkerer", \
			    "Dedicated Tinkerer", \
			    "Experienced Tinkerer", \
			    "Master Tinkerer", \
			    "Novice Mechanic", \
			    "Mechanic", \
			    "Master Mechanic", \
			    "Craftsgnome", \
			    "Craft Master", \
			    "Assistant Head Tinkerer", \
			    "Head Tinkerer"})
#define GNOME_TITLES_F ({"", "New Krynn Gnome", \
			    "Gnome Aide", \
     			    "Gnome Mate", \
     			    "Novice Tinkeress", \
    			    "Dedicated Tinkeress", \
			    "Experienced Tinkeress", \
			    "Mistress Tinkeress", \
     			    "Novice Mechanic", \
			    "Mechanic", \
   			    "Mistress Mechanic", \
 			    "Craftsgnome", \
 			    "Craft Mistress", \
 			    "Assistant Head Tinkeress", \
 			    "Head Tinkeress"})
#define L2               3
#define L3               6
#define L4              10
#define L5              15
#define L6              20
#define L7              25
#define L8              30
#define L9              35
#define L10             40

#define MAX_TRAIN       ({20, 30, 40, 50, 60, 65, 70, 75, 80, 90, 100})
#define GMEMBER_BIT     15
#define GQUEST_BIT      14
#define GGUILD_GROUP    1
#define GMEMBER(x)      x->test_bit("Krynn", GGUILD_GROUP, GMEMBER_BIT)

#define JOINLOG         GGUILD + "log/guild_members.log"
#define LEAVELOG        GGUILD + "log/guild_leavers.log"
#define PROMOTELOG 	GGUILD + "log/promote.log"
#define GOT_PROMOTED	GGUILD + "log/got_promoted.log"
#define ALL_PROMOTE_LOG GGUILD + "log/all_promote.log"
#define FOLDER_DIR	GGUILD + "log/folders/"
#define GMASTER_SAVE	GGUILD + "log/head_tinker_name"
#define HEAD_TIN_DUTIES GGUILD + "log/head_tin_duties"
#define HEAD_TIN_MESSAGE GGUILD+ "log/head_tin_message"

#define SS_BUILD        108200 /* 108000 - 108999 */
#define SS_PROMOTE	108201
#define KGN_SUB 	"_kgnome_subloc"
