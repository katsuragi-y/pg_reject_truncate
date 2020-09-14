#include "postgres.h"

#include "tcop/utility.h"
#include "nodes/nodes.h"
#include "fmgr.h"

PG_MODULE_MAGIC;

static ProcessUtility_hook_type prev_ProcessUtility = NULL;

extern ProcessUtility_hook_type ProcessUtility_hook;

void _PG_init(void);
void _PG_fini(void);
static void pgrt_ProcessUtility(PlannedStmt *pstmt, const char *queryString,
                                ProcessUtilityContext context, ParamListInfo params,
                                QueryEnvironment *queryEnv,
                                DestReceiver *dest, QueryCompletion *qc);

void
_PG_init(void)
{
	prev_ProcessUtility = ProcessUtility_hook;
	ProcessUtility_hook = pgrt_ProcessUtility;
}

void
_PG_fini(void)
{
	ProcessUtility_hook = prev_ProcessUtility;
}

static void
pgrt_ProcessUtility(PlannedStmt *pstmt, const char *queryString,
                                ProcessUtilityContext context, ParamListInfo params,
                                QueryEnvironment *queryEnv,
                                DestReceiver *dest, QueryCompletion *qc)
{
	Node	*parsetree = pstmt->utilityStmt;

	/*
	 * if statements is truncate, rejecet it
	 */
	if (nodeTag(parsetree) == T_TruncateStmt)
	{
	    ereport(ERROR,
    	        (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
        	     errmsg("TRUNCATE IS NOT ALLOWED")));
	}

	standard_ProcessUtility(pstmt, queryString,
							context, params, queryEnv,
							dest, qc);
}
