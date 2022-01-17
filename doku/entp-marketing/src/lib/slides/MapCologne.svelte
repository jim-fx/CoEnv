<script lang="ts">
	import { fade } from 'svelte/transition';

	import Map from './cologne.svelte';
	export let step;
</script>

<div class="step-{step}" transition:fade>
	<h1 absolute text-8xl>Potential Customers</h1>
	<div class="map">
		<Map showMarkers={step > 0} />
	</div>
</div>

<style lang="scss">
	.step-0 .map {
		opacity: 0.5;
	}

	h1 {
		transform-origin: 0 0;
		transition: transform 0.5s ease;
	}

	.map {
		transition: transform 0.5s ease, filter 0.5s ease;
	}

	.step-0 {
		h1 {
			transform: translate(calc(50vw - 50%), calc(50vh - 50%));
		}
		.map {
			filter: blur(2px);
			transform: perspective(100px) rotate3d(1, 1, 1, 0deg) scale(0.6);
		}
	}
	.step-1 {
		h1 {
			transform: translate(10px, 10px) scale(0.4);
		}
		.map {
			filter: blur(0px);
			transform: perspective(100px) rotate3d(1, 1, 1, 2deg) scale(0.9);
		}
	}
</style>
