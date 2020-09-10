MODULE_big = pg_reject_truncate
OBJS = pg_reject_truncate.o
EXTENSION = pg_reject_truncate
DATA = pg_reject_truncate--1.0.sql

#REGRESS_OPTS = --temp-config $(top_srcdir)/contrib/pg_stat_statements/pg_stat_statements.conf
REGRESS = pg_reject_truncate

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
