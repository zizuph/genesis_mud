/*
   /d/Kalad/sys/macros.h
   
   Kalad macros.
   
   Fysix@Genesis, Oct 1997
 */
#ifndef _KALAD_MACROS_DEF
#define _KALAD_MACROS_DEF

#include <stdproperties.h>

#define TP	this_player()
#define TO	this_object()
#define TI	this_interactive()

#define HE(x)	(x)->query_pronoun()
#define HIS(x)	(x)->query_possessive()
#define HIM(x)	(x)->query_objective()

#define CAP	capitalize
#define ENV	environment
#define NF	notify_fail

#define INSIDE	add_prop(ROOM_I_INSIDE, 1)

/*******************************************************
 *   Common useful macros
 *******************************************************/
#define BS(msg)          break_string(msg,70)
#define TP_N             TP->query_name()
#define PO               previous_object()
#define AA(xx,yy)        add_action("xx","yy")
#define E(obj)           environment(obj)
#define P(str,ob)        present(str,ob)
#define C(xxx)           capitalize(xxx)
#define L(str)           lower_case(str)
#define AINV(ob)         all_inventory(ob)
#define DINV(ob)         deep_inventory(ob)
#define FN(ob)           file_name(ob)
#define ALARM(time,fun)  set_alarm(time,0.0,"fun") /* an easy alarm     */

#endif
