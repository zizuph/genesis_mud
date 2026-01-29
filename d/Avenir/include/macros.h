// file name:        /d/Avenir/include/macros.h
// creator(s):       Cirion
// revision history: Denis, Mar'97: Added some of the definitions from
//				    /d/Avenir/common/common.h
//                  Cirion 1999.03.13 Removed references to Roke
//                  Lilith Jan 2022, made it so IN_IN also adds
//                     the ROOM_I_INSIDE prop.
// purpose:          
// note:             
// bug(s):           
// to-do:            
#ifndef __AVENIR_MACROS
#define __AVENIR_MACROS
/*
 * SCROLLING_LOG will keep logs under 10k, for use with things
 * we just want to keep an eye on, not important information.
 */
#define SCROLLING_LOG(file, entry)  ((file_size(file) > 10000) ? \
    (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
    (write_file(file, ctime(time()) + ": " + entry + "\n")))

// Rooms not affected by the light flux (/d/Avenir/common/source_flux)
#define IN_IN	add_prop("_not_in_flux_zone", 1);   \
                add_prop(ROOM_I_INSIDE, 1);   \
	            remove_prop(ROOM_I_ALLOW_STEED);    \
		        add_prop(ROOM_I_NO_ALLOW_STEED, 1);

// Kill thief on sight for the npcs inheritiiong /d/Avenir
#define KILL_THIEF	add_prop("_live_m_attack_thief", "thief_fun")

// Special flux message.
#define FLUX(x)		("/d/Avenir/common/source_flux")->special_flux(x)

#define ALLBB(actor, message)    FILTER_CAN_SEE_IN_ROOM( \
      FILTER_IS_SEEN(actor, \
      FILTER_LIVE(all_inventory(environment(actor)) - \
          ({actor}))))->catch_msg(message);

#endif  /* __AVENIR_MACROS */
