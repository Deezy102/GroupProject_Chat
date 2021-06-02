CREATE database chat;

\c chat

CREATE TABLE "chatlist" (
	"id" serial NOT NULL,
	"chatname" varchar(50) NOT NULL,
	"userlist" text[] NOT NULL,	
	CONSTRAINT "chatlist_pk" PRIMARY KEY ("id")
) WITH (
  OIDS=FALSE
);

CREATE TABLE "users" (
	"id" serial NOT NULL,
	"login" varchar(50) NOT NULL,
	"password" varchar(50) NOT NULL,
	"current_socket" integer,
	CONSTRAINT "users_pk" PRIMARY KEY ("id")
) WITH (
  OIDS=FALSE
);