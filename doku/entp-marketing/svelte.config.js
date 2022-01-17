import preprocess from 'svelte-preprocess';
import Unocss from 'unocss/vite'
import presetIcons from '@unocss/preset-icons'
import presetAttributify from '@unocss/preset-attributify'
import presetUno from '@unocss/preset-uno'
import ViteFonts from 'vite-plugin-fonts'
import AdapterStatic from "@sveltejs/adapter-static"

const { BASE_PATH = "" } = process.env;

/** @type {import('@sveltejs/kit').Config} */
const config = {
  // Consult https://github.com/sveltejs/svelte-preprocess
  // for more information about preprocessors
  preprocess: preprocess(),

  kit: {
    // hydrate the <div id="svelte"> element in src/app.html
    target: '#svelte',
    paths: { base: BASE_PATH },
    adapter: AdapterStatic(),
    vite: {
      plugins: [
        Unocss({
          shortcuts: [
            {
              "center": "grid content-center justify-center h-full w-full",
              "half": "w-1/2 h-1/2"
            }
          ],
          presets: [
            presetUno(),
            presetIcons(),
            presetAttributify()
          ]
        }),
        ViteFonts.default({
          google: {
            families: ['Space Mono']
          },
        })
      ],
    },
  }
};

export default config;
