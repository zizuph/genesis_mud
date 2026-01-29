/* This file was created because of /d/Emerald/defs.h unreliablity. */
/* It is not just a straight copy, but just a cut down version with */
/* only the bits I require. The intention is to keep this file as   */
/* short and simple as possible, so that it needs to be changed as  */
/* infrequently as possible.                                        */
/* This should make important objects (eg. guild stuff) less prone  */
/* to other wizards mistakes.                                       */
/* Coded 19/12/95 by Tulix III.                                     */
/* P.S. Think more than twice about changing this code.             */

#define HOME_DIR      "/d/Emerald/"

#define CAVE_DIR       "/d/Emerald/mountains/mtblack/cave/"
#define GRUNTS_DIR    "/d/Emerald/common/guild/grunts/"

#define TP            this_player()
#define TO            this_object()

#define NF(x)         notify_fail(x)

#define CAP(x)        capitalize(x)
#define HE_SHE(x)     x->query_pronoun()
#define PRON(x)       HE_SHE(x)
#define HIS_HER(x)    x->query_possessive()
#define POS(x)        HIS_HER(x)
#define HIM_HER(x)    x->query_objective()
#define ENV(x)        environment(x)
