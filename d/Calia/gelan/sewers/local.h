 /*****************************************************************************
*  /d/Calia/gelan/sewers
*
*  Description: Sewers of Gelan
*
*  Created Aug 2021, Greneth
*
 *****************************************************************************/
 
 /*****************************************************************************
*  Standard include files
 *****************************************************************************/
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <const.h> 
#include <money.h>
#include <composite.h>
#include <formulas.h>
#include <options.h>

 /****************************************************************************
*  Macros
 ****************************************************************************/
#define BS(msg)          break_string(msg,70)
#define TP               this_player()
#define TP_N             TP->query_name()
#define TO               this_object()
#define PO               previous_object()
#define AA(xx,yy)        add_action("xx","yy")
#define E(obj)           environment(obj)
#define P(str,ob)        present(str,ob)
#define NF(xxx)          notify_fail(xxx)
#define C(xxx)           capitalize(xxx)
#define L(str)           lower_case(str)
#define HE(who)          who->query_pronoun()
#define HIS(who)         who->query_possessive()
#define HIM(who)         who->query_objective()
#define AINV(ob)         all_inventory(ob)
#define DINV(ob)         deep_inventory(ob)
#define FN(ob)           file_name(ob)
#define ALARM(time,fun)  set_alarm(time,0.0,"fun")

#define SMELL_CON        164

 /******************************************************************************
*  Paths
 *****************************************************************************/
#define PARENT                   "/d/Calia/gelan/sewers/"
#define LOG_DIR                  PARENT + "logs/"
#define STDIR                    PARENT + "std/"
#define RDIR                     PARENT + "rooms/"
#define ARM                      PARENT + "arm/"
#define WEP                      PARENT + "wep/"
#define OBJ                      PARENT + "obj/"
#define LIV                      PARENT + "npc/"
#define SPELLS                   PARENT + "spells/"
#define FIRST_FLOOR              RDIR   + "first_floor/"
#define SEWERS_STD               STDIR  + "sewers_std"

 /******************************************************************************
*  Exits
 *****************************************************************************/
#define NORMAL_EXITS (["nw":"northwest", "n":"north", "ne":"northeast",\
   "e":"east", "se":"southeast", "s":"south", "sw":"southwest", "w":"west"])
	 
 /******************************************************************************
*  Short Desc - First Floor
 *****************************************************************************/
#define S_N  "In the northern part of the sewers"
#define S_E "In the eastern part of the sewers"
#define S_S  "In the southern part of the sewers"
#define S_W "In the western part of the sewers"
#define S_M  "In the middle of the sewers"