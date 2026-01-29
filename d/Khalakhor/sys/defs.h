#ifndef KHALAKHOR_DOMAIN_DEFS
#define KHALAKHOR_DOMAIN_DEFS

#define TP           this_player()
#define TO           this_object()
#define TI           this_interactive()
#define TPQN         this_player()->query_name()
#define TPQRN        this_player()->query_real_name()
#define TIQN         this_interactive()->query_name()
#define TIQRN        this_interactive()->query_real_name()
#define HIS          this_player()->query_possessive()
#define HIM          this_player()->query_objective()
#define RACE         this_player()->query_race()
#define RACENAME     this_player()->query_race_name()
#define HE           this_player()->query_pronoun()
   
#define HERE(x)      present(x, TO)

#define HIS_HER(ob)  ob->query_possessive()
#define HIM_HER(ob)  ob->query_objective()
#define HE_SHE(ob)   ob->query_pronoun()
#define FIX_EUID seteuid(getuid(this_object()))

#define ENV(ob)      environment(ob)
#define ETO          (environment(this_object()))
#define FETO         (file_name(environment(this_object())))
                      
#define NF(x)        notify_fail(x)
#define NF0(x)       { notify_fail(x+"\n"); return 0; }

// This definition is only kept for backward compatibility. You should use
// the simul-efun one_of_list(x) instead.
#define ONE_OF(x)    one_of_list(x)

#define KSTDELF      "/d/Khalakhor/std/npc/elf"
#define KSTDROOM     "/d/Khalakhor/std/room"
#define KLOGGER      "/d/Khalakhor/lib/logger"

#define EXISTS(x)    file_size(x + ".c") >  0
#define EXISTS0(x)   file_size(x + ".c") >= 0

//  No more defines after this line.
#endif
