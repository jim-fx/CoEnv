<script lang="ts">
	import { SlideChanger, SlideProgress, SlideTime, SlideTitle } from '$lib/components';
	import { HexagonBackground } from '$lib/elements';
	import { showBackground } from '$lib/stores';
	import { fade } from 'svelte/transition';
	import 'uno.css';
	import './global.scss';

	let showTime = true;

	function handleKeyDown({ key }) {
		if (key === 'c') showTime = !showTime;
	}
</script>

<svelte:window on:keydown={handleKeyDown} />

<main w-screen h-screen overflow-hidden>
	<slot />
	{#if $showBackground}
		<div opacity-20 absolute transition:fade style="z-index: -1;">
			<HexagonBackground />
		</div>
	{/if}

	<SlideProgress />
	{#if showTime}
		<SlideTime />
	{/if}
	<SlideTitle />
	<SlideChanger />
</main>
