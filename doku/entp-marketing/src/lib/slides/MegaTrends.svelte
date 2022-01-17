<script lang="ts">
	import { onMount } from 'svelte';
	import { scale, fade } from 'svelte/transition';

	import Map from './trendmap.svelte';

	let visible = false;

	export let step;

	onMount(() => {
		setTimeout(() => {
			visible = true;
		}, 50);
	});
</script>

<div class="step-{step}" class:visible transition:fade>
	<h1 text-8xl absolute z-1 shadow-4xl>Megatrends</h1>
	<div id="map" style={`opacity: ${step < 1 ? 0.5 : 1}`}>
		<Map {visible} newWork={step > 0} showText={step > 0} />
	</div>
</div>

<style>
	#map {
		transform: perspective(100vh) rotate3d(1, 1, 1, 0deg) scale(0);
		opacity: 0;
		transition: opacity 1s ease, transform 1s ease;
	}

	.visible > #map {
		opacity: 1;
	}

	.step-0.visible > #map {
		transform: perspective(100vh) rotate3d(16, -16, -3, 20deg) scale(1.5);
	}

	.step-1.visible > #map {
		transform: perspective(100vh) rotate3d(1, 1, 1, 10deg) translate(20%, -20%) scale(1.2);
	}

	h1 {
		transition: transform 0.3s ease;
		transform-origin: 0 0;
	}

	.step-0 h1 {
		transform: translate(calc(50vw - 50%), calc(50vh - 50%)) scale(1);
	}

	.step-1 h1 {
		transform: translate(1.25rem, 1.25rem) scale(0.4);
	}
</style>
