import { browser } from "$app/env";
import { get, writable } from "svelte/store";


export const slideIndex = writable(0);
if (browser) {
  if (window.location.hash) {
    const index = parseInt(window.location.hash.replace("#", ""));
    slideIndex.set(index);
  }
  slideIndex.subscribe(v => {
    window.location.hash = v + "";
  })
}

export const slideTime = writable(180);

export const slideAmount = writable(0);

export const showBackground = writable(true);

export const slideTitle = writable("")

let timerInt;
let startTime;
function resetStartTimer() {
  clearInterval(timerInt);
  startTime = Date.now();
  timerInt = setInterval(() => {
    slideTime.set(Math.floor((Date.now() - startTime) / 1000))
  }, 1000);
}

export const nextSlide = () => {
  if (get(slideIndex) === 0) resetStartTimer();
  if (get(slideIndex) === get(slideAmount) - 1) clearInterval(timerInt);
  slideIndex.update((index) => Math.min(get(slideAmount) - 1, index + 1));
};

export const previousSlide = () => slideIndex.update((index) => Math.max(0, index - 1));

