<script lang="ts">
	import { Hexagon } from '$lib/elements';
	import { onMount } from 'svelte';
	import { fade, scale } from 'svelte/transition';

	let visible = false;
	onMount(() => {
		setTimeout(() => {
			visible = true;
		}, 100);
	});
</script>

<div center transition:fade>
	<h1 transition:scale text-8xl>Thank you for <br /> your attention</h1>
	<a
		text-2xl
		color-white
		mt-10
		text-center
		w-full
		no-underline
		href="https://github.com/jim-fx/CoEnv"
		>For more information visit: <br /><b>github.com/jim-fx/CoEnv</b></a
	>
	<div class="-z-1" absolute w-full h-full style="filter: blur(2px)">
		{#each Array(20) as _, i}
			<div class="wrapper" style="--index: {i};">
				<div class="anim-wrapper">
					<Hexagon --fill="none" --stroke="white" animated visibleDelay={i * 200} />
				</div>
			</div>
		{/each}
	</div>
</div>

<style>
	.wrapper {
		position: absolute;
		opacity: 0.5;
		width: 100%;
		transform: scale(calc(var(--index) * 0.1));
		height: 100%;
		opacity: calc(1 - var(--index) * 0.08);
	}

	.anim-wrapper {
		width: 100%;
		height: 100%;
		animation: booink 20s cubic-bezier(0.8, -0.02, 0.27, 0.99) infinite;
		animation-delay: calc(var(--index) * 100ms);
	}

	@keyframes booink {
		0% {
			transform: scale(1) rotate(0deg);
		}
		10% {
			transform: scale(1.1) rotate(0deg);
		}
		20% {
			transform: scale(1.1) rotate(60deg);
		}

		30% {
			transform: scale(1) rotate(60deg);
		}

		100% {
			transform: scale(1) rotate(60deg);
		}
	}
</style>
