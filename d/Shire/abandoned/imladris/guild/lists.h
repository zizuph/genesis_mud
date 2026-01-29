#ifndef H_LIST_H
#define H_LIST_H

#define L_DM 0	 /* Detection Mastery */
#define L_SD 1	 /* Spell Defence     */
#define L_CW 2	 /* Concussion's Way  */
#define L_BL 3	 /* Barrier Law       */
#define L_FL 4	 /* Fire Law	      */
#define L_LW 5	 /* Light's Law       */

#define LIST_TAX    ({ 3, 3, 7, 4, 12, 8 })

#define LIST_FILES  ({ DETECTION_MASTERY, SPELL_DEFENCE, \
                       CONCUSSIONS_WAY, \
		       BARRIER_LAW, LIGHTS_WAY })

#endif
