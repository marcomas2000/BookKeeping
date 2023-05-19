drop procedure if exists deleteEntry;
create procedure deleteEntry(in code varchar(6))
delete from JournalEntry where JECode=code;

drop procedure if exists deleteEntryCredit;
create procedure deleteEntryCredit(in code varchar(6))
delete from JECreditAccounts where JECode=code;

drop procedure if exists deleteEntryDebit;
create procedure deleteEntryDebit(in code varchar(6))
delete from JEDebitAccounts where JECode=code;

drop procedure if exists getAccountDesc;
create procedure getAccountDesc()
select AccountDescription from Account order by AccountDescription;

drop procedure if exists getAccountName;
create procedure getAccountName(in code varchar(6))
select AccountDescription from Account where AccountCode=code;

DROP PROCEDURE IF EXISTS getAcctCodeFromDesc;
CREATE PROCEDURE getAcctCodeFromDesc (in descr varchar(100))
select AccountCode from Account where AccountDescription = descr;

drop procedure if exists getEntryAcctCreditData;
create procedure getEntryAcctCreditData(in code varchar(6))
select JECAAccountCode, JECAMemo, JECAAmount from JECreditAccounts where JECode=code;

drop procedure if exists getEntryAcctDebitData;
create procedure getEntryAcctDebitData(in code varchar(6))
select JEDAAccountCode, JEDAMemo, JEDAAmount from JEDebitAccounts where JECode=code;

drop procedure if exists getEntryGenData;
create procedure getEntryGenData(in code varchar(6))
select JEDateEvent, JEDatePosted, JEDescription from JournalEntry where JECode=code;

drop procedure if exists getEntryGenDataList;
create procedure getEntryGenDataList()
select JEDateEvent, JECode, JEDescription, JEDatePosted from JournalEntry order by JEDateEvent;

drop procedure if exists insertEntry;
CREATE PROCEDURE insertEntry (IN entryCode varchar(6),IN descr varchar(200),IN datePosted date,IN dateEvent date)
INSERT INTO JournalEntry VALUES (entryCode, descr, datePosted, dateEvent);

drop procedure if exists insertEntryAcctDeb;
CREATE PROCEDURE insertEntryAcctDeb (IN entryCode varchar(6),IN acctCode varchar(4),IN amount double,IN memo varchar(200))
INSERT INTO JEDebitAccounts VALUES (entryCode, acctCode, amount, memo);

drop procedure if exists insertEntryAcctCred;
CREATE PROCEDURE insertEntryAcctCred (IN entryCode varchar(6),IN acctCode varchar(4),IN amount double,IN memo varchar(200))
INSERT INTO JECreditAccounts VALUES (entryCode, acctCode, amount, memo);

drop procedure if exists getAccountEntries;
create procedure getAccountEntries(in code varchar(4))
(select a.JECode, a.JEDateEvent, "D" as type, b.JEDAMemo, b.JEDAAmount
 from JournalEntry a, JEDebitAccounts b
 where a.JECode = b.JECode and b.JEDAAccountCode=code) 
union 
(select a.JECode, a.JEDateEvent, "C" as type, b.JECAMemo, b.JECAAmount  
from JournalEntry a, JECreditAccounts b 
where a.JECode = b.JECode and b.JECAAccountCode=code)
order by JEDateEvent;
