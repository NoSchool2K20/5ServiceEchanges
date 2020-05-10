# Equipe 5 : Notes relatives a l'implementation de RabbitMQ

Service Echanges: Send Mails from amqp messages, cronjob to send invoices monthly parsing a csv file

[Rabbit Wiki](https://github.com/NoSchool2K20/Organisation/wiki/RabbitMQ)

Installation:

```text
cd 5ServiceEchanges/
npm install
```

Build : 

```text
npm run build
```

Lauch App: Start a service listening on port 8080, 3 amqp listeners and a cron jon to send invoices:

```text
cd 5ServiceEchangess/
node src/Index.bs.js
```
