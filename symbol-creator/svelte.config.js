import preprocess from 'svelte-preprocess';
import adapterStatic from "@sveltejs/adapter-static";


const { BASE_URL = "" } = process.env;

/** @type {import('@sveltejs/kit').Config} */
const config = {
  preprocess: preprocess(),
  kit: {
    adapter: adapterStatic(),
    appDir: "app",
    paths: {
      base: (BASE_URL.startsWith("/") || !BASE_URL.length) ? BASE_URL : "/" + BASE_URL,
    },
    // hydrate the <div id="svelte"> element in src/app.html
    target: '#svelte'
  }
};

export default config;
