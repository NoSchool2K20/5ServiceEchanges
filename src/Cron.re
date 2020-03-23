open BsCron
 
// Make a job that will fire every second when started
let job =
  CronJob.make(
    `CronString("* * * * * *"),
    _ => Js.log("Just doing my job"),
    (),
  );

let minuteJob =
CronJob.make(
  `CronString("30 * * * * *"),
  _ => Js.log("Just doing my minute job"),
  (),
);
 
// Firing every second, printing 'Just doing my job'
start(job);
start(minuteJob);

