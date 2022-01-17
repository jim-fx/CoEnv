export function humaneNumbers(bytes: number): string {
  if (!bytes) return "0";
  const s = ['', 'Tsd.', 'Mil.', 'GB', 'TB', 'PB'];
  const e = Math.floor(Math.log(bytes) / Math.log(1000));
  return (bytes / Math.pow(1000, e)).toFixed(2) + " " + s[e];
}
